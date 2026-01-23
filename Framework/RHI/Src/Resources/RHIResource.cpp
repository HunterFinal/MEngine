#include "Resources/RHIResource.h"

#include "Macro/AssertionMacros.h"
#include "Macro/BitOperationMacros.h"

#include <atomic>
#include <type_traits>

#include <unordered_set>



namespace MEngine
{

namespace RHI
{

struct MRHIResource::RefCountImpl
{
  static constexpr uint8 REF_COUNT_TYPE_BIT = sizeof(RefCountType) * 8;

  static constexpr RefCountType MARK_DISPOSE_MASK = static_cast<RefCountType>(1) << (REF_COUNT_TYPE_BIT - 2);
  static constexpr RefCountType DISPOSED_MASK     = static_cast<RefCountType>(1) << (REF_COUNT_TYPE_BIT - 1);
  static constexpr RefCountType REF_COUNT_MASK    = ~(DISPOSED_MASK | MARK_DISPOSE_MASK);

  std::atomic<RefCountType> Combined;

  RefCountType_Signed AddRef()
  {
    const RefCountType prevVal = Combined.fetch_add(1, std::memory_order_acquire);
    me_assert((prevVal & DISPOSED_MASK) == 0);
    // Check overflow
    const RefCountType prevRefCount = prevVal & REF_COUNT_MASK;
    me_assert(prevRefCount < REF_COUNT_MASK);
    
    return static_cast<RefCountType_Signed>(prevRefCount + 1);
  }

  RefCountType_Signed RemoveRef()
  {
    const RefCountType prevVal = Combined.fetch_sub(1, std::memory_order_release);
    me_assert((prevVal & DISPOSED_MASK) == 0);
    // Check underflow
    const RefCountType prevRefCount = prevVal & REF_COUNT_MASK;
    me_assert(prevRefCount > 0);
    
    return static_cast<RefCountType_Signed>(prevRefCount - 1);
  }

  RefCountType_Signed GetRefCount()
  {
    return Combined.load(std::memory_order_relaxed) & REF_COUNT_MASK;
  }

  bool IsValid()
  {
    RefCountType curtVal = Combined.load(std::memory_order_relaxed);
    // Mark dispose bit is 0 and
    // the reference count should greater than 0 
    return ((curtVal & MARK_DISPOSE_MASK) == 0) && ((curtVal & REF_COUNT_MASK) != 0);
  }

  // Returns true if this resource was already marked for dispose, otherwise false
  bool MarkDispose()
  {
    RefCountType prevVal = Combined.fetch_or(MARK_DISPOSE_MASK, std::memory_order_release);
    me_assert((prevVal & DISPOSED_MASK) == 0);
    return (prevVal & MARK_DISPOSE_MASK) != 0;
  }

  // Returns true if this resource was unmarked for dispose, false otherwise
  bool UnmarkDispose()
  {
    RefCountType prevVal = Combined.fetch_and(~MARK_DISPOSE_MASK, std::memory_order_release);
    me_assert((prevVal & DISPOSED_MASK) == 0);
    return (prevVal & MARK_DISPOSE_MASK) != 0;
  }

  bool Disposing()
  {
    RefCountType curtVal = Combined.load(std::memory_order_acquire);
    // Check resource state for save disposing.
    // The mark dispose bit should be 1 and the disposed bit should be 0
    me_assert(((curtVal & MARK_DISPOSE_MASK) != 0));
    me_assert(((curtVal & DISPOSED_MASK) == 0));
    RefCountType curtRefCount = curtVal & REF_COUNT_MASK;

    // No reference of this resource.So we dispose it 
    if (curtRefCount == 0)
    {
      Combined.fetch_or(DISPOSED_MASK, std::memory_order_acquire);
      return true;
    }
    // We can not dispose a resource that still has any reference
    else
    {
      (void)UnmarkDispose();
      return false;
    }
  }

};

} // namespace MEngine::RHI

} // namespace MEngine

namespace MEngine::RHI::Internal
{
  void FlushResourceToDelete();
  // TODO We currently manage all pending delete resource on single thread
  // TODO Once we switch to multithread we should also change implementation too
  class MRHIResourceManager final
  {
    public:
      static MRHIResourceManager& Get()
      {
        static MRHIResourceManager s_Instance;
        return s_Instance;
      }

      void EnqueuePendingDelete(IN MEngine::RHI::MRHIResource* PendingDeleteResource)
      {
        me_assert(PendingDeleteResource != nullptr);

        // Call DestroyUntracked
        if (PendingDeleteResource->IsUntracked())
        {
          PendingDeleteResource->DestroyUntracked();
          return;
        }

        m_pendingDeletes.emplace(PendingDeleteResource); 
      }

      void FlushTrackedDeletingResources()
      {
        for (MEngine::RHI::MRHIResource* resource : m_pendingDeletes)
        {
          if (resource->m_pRefCountImpl->Disposing())
          {
            delete resource;
          }
        }

        m_pendingDeletes.clear();
      }

    private:
      std::unordered_set<MEngine::RHI::MRHIResource*> m_pendingDeletes;
  };
}

namespace MEngine
{

namespace RHI
{

MRHIResource::MRHIResource(IN EResourceType InType)
  : mc_type{InType}
  , m_pRefCountImpl{std::make_unique<MRHIResource::RefCountImpl>()}
  , m_trackState{Untracked}
{}

MRHIResource::~MRHIResource()
{
  me_assert(m_pRefCountImpl->GetRefCount(/**std::memory_order_relaxed */) == 0);
}

MRHIResource::RefCountType MRHIResource::AddRef() const
{
  // We must add reference count before we use the resource
  // @see std::memory_order_acquire
  RefCountType_Signed newRefCount = m_pRefCountImpl->AddRef(/**std::memory_order_acquire */);
  me_assert(newRefCount > 0);
  return static_cast<RefCountType>(newRefCount);
}

MRHIResource::RefCountType_Signed MRHIResource::RemoveRef() const
{
  // We must remove reference count after we dispose the resource
  // @see std::memory_order_release
  RefCountType_Signed newRefCount = m_pRefCountImpl->RemoveRef(/**std::memory_order_release */);
  me_assert(newRefCount >= 0);
  
  if (newRefCount == 0)
  {
    // Mark this as a dispose resource
    MarkDispose();
  }

  return static_cast<RefCountType>(newRefCount);
}

MRHIResource::RefCountType MRHIResource::GetRefCount() const
{
  RefCountType_Signed curtVal = m_pRefCountImpl->GetRefCount(/**std::memory_order_relaxed */);
  me_assert(curtVal >= 0);
  return static_cast<RefCountType>(curtVal);
}

bool MRHIResource::IsValid() const
{
  return m_pRefCountImpl->IsValid(/**std::memory_order_relaxed */);
}
  
void MRHIResource::MarkDispose() const
{
  if (!m_pRefCountImpl->MarkDispose(/**std::memory_order_release */))
  {
    MEngine::RHI::Internal::MRHIResourceManager::Get().EnqueuePendingDelete(const_cast<MRHIResource*>(this));
  }
}

} // namespace MEngine::RHI

} // namespace MEngine

namespace MEngine::RHI::Internal
{
  void FlushResourcesToDelete()
  {
    MRHIResourceManager::Get().FlushTrackedDeletingResources();
  }
} // namespace MEngine::RHI::Internal