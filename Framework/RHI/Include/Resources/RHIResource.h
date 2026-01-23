#pragma once

#ifndef _ME_RHI_RESOURCE_
#define _ME_RHI_RESOURCE_

#include "RHIDefines.h"
#include "RHITypes.h"
#include "Utils/RHIRefCountPtr.h"

#include <memory>
#include <type_traits>

template<typename RHIDerivedType, typename... Args>
Requires_Derived_From(RHIDerivedType, MEngine::RHI::MRHIResource)
RHIDerivedType* RHINewObject(Args&&... Arg);

namespace MEngine
{

namespace RHI
{

namespace Internal
{
  class MRHIResourceManager;
} // namespace MEngine::RHI::Internal

class MRHIResource
{

// TODO For temporary use
TYPEDEF(uint64, RefCountType);
TYPEDEF(std::make_signed_t<RefCountType>, RefCountType_Signed);

private:
  enum ETrackState
  {
    Untracked,
    Tracked
  };

protected:
  RHI_API MRHIResource(IN EResourceType InType);
  // Manual deletion is prohibited.
  // Resources are managed by RHI.
  RHI_API virtual ~MRHIResource();

  // Override this if user do not use deleter of RHIResourceManager
  RHI_API virtual void DestroyUntracked() {}

public:
  RHI_API RefCountType AddRef() const;
  RHI_API RefCountType_Signed RemoveRef() const;
  RHI_API RefCountType GetRefCount() const;
  RHI_API bool IsValid() const;
  
  MEngine::RHI::EResourceType GetType() const { return mc_type; }
  
private:
  void MarkDispose() const;

  static void MarkAsTracked(IN MEngine::RHI::MRHIResource* Resource)
  {
    Resource->m_trackState = Tracked;
  }

  bool IsUntracked() const { return m_trackState == Untracked; }

private:

  friend class MEngine::RHI::Internal::MRHIResourceManager;

  template<typename RHIDerivedType, typename... Args>
  Requires_Derived_From(RHIDerivedType, MEngine::RHI::MRHIResource)
  friend RHIDerivedType* ::RHINewObject(Args&&... Arg);

  const MEngine::RHI::EResourceType mc_type;

  struct RefCountImpl;
  mutable std::unique_ptr<RefCountImpl> m_pRefCountImpl; 

  ETrackState m_trackState;
};

} // namespace MEngine::RHI

} // namespace MEngine

template<typename RHIDerivedType, typename... Args>
Requires_Derived_From(RHIDerivedType, MEngine::RHI::MRHIResource)
RHIDerivedType* RHINewObject(Args&&... Arg)
{
  static_assert(std::is_base_of_v<MEngine::RHI::MRHIResource, RHIDerivedType>, "Can not create a non-derived object of MEngine::RHI::MHIResource");
  RHIDerivedType* result = new RHIDerivedType{std::forward<Args>(Arg)...};
  MEngine::RHI::MRHIResource::MarkAsTracked(result);
  return result;

}

#endif // _ME_RHI_RESOURCE_