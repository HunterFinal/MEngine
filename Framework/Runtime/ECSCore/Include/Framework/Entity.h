#pragma once

#ifndef _ME_RUNTIME_ECSCORE_ENTITY_
#define _ME_RUNTIME_ECSCORE_ENTITY_

#include "Config/ECSConfig.h"

namespace MEngine
{

namespace ECSCore
{

template<typename EntityPolicyType>
class MEntity
{
  using EntityIDType = typename EntityPolicyType::Entity_ID_Type;
  inline static constexpr EntityIDType EntityIDMask = EntityPolicyType::ID_Mask;
  inline static constexpr EntityIDType InvalidEntity = EntityPolicyType::ID_Invalid;

  public:
    bool IsValid() const
    {
      return (m_ID & EntityIDMask) != InvalidEntity;
    }

    explicit operator bool() const
    {
      return IsValid();
    }

    const EntityIDType& GetID() const 
    { 
      return m_ID;
    }

    void Reset()
    {
      m_ID = InvalidEntity;
    }

  private:
    explicit constexpr MEntity()
      : m_ID(InvalidEntity)
    { }

  private:
    EntityIDType m_ID;
};

template<typename EntityPolicyType>
bool operator==(const MEntity<EntityPolicyType>& Lhs, const MEntity<EntityPolicyType>& Rhs)
{
  return Lhs.GetID() == Rhs.GetID();
}

template<typename EntityPolicyType, typename DiffPolicyType>
bool operator==(const MEntity<EntityPolicyType>& Lhs, const MEntity<DiffPolicyType>& Rhs)
{
  // FIXME 
  return false;
}

} // namespace MEngine::ECS

} // namespace MEngine


#endif // _ME_RUNTIME_ECSCORE_ENTITY_