#pragma once

#ifndef _ME_RHI_RESOURCE_
#define _ME_RHI_RESOURCE_

#include "RHIDefines.h"
#include "RHITypes.h"
#include "Utils/RHIRefCountPtr.h"

#include <memory>

namespace MEngine
{

namespace RHI
{

class MRHIResource
{

// TODO For temporary use
TYPEDEF(uint64, RefCountType);
TYPEDEF(std::make_signed_t<RefCountType>, RefCountType_Signed);

protected:
  // Manual deletion is prohibited.
  // Resources are managed by RHI.
  RHI_API virtual ~MRHIResource();

public:
  RHI_API MRHIResource(IN EResourceType InType);
  RHI_API RefCountType AddRef() const;
  RHI_API RefCountType_Signed RemoveRef() const;
  RHI_API RefCountType GetRefCount() const;
  RHI_API bool IsValid() const;
  
  MEngine::RHI::EResourceType GetType() const { return mc_type; }
  
private:
  void MarkDispose() const;

private:
  const MEngine::RHI::EResourceType mc_type;

  struct RefCountImpl;
  mutable std::unique_ptr<RefCountImpl> m_pRefCountImpl; 

};

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_RESOURCE_