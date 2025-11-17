#pragma once

#ifndef _ME_RUNTIME_ECSCORE_ENTITY_
#define _ME_RUNTIME_ECSCORE_ENTITY_

#include "Config/ECSConfig.h"
#include "Core/BitLib.h"

namespace MEngine
{

namespace ECSCore
{

template<typename EntityPolicyType>
class MEntity
{
  friend class MEntityWorld;

  using EntityType = typename EntityPolicyType::Entity_Type;
  using IDType = typename EntityPolicyType::ID_Type;
  using GenerationType = typename EntityPolicyType::Generation_Type;
  inline static constexpr IDType EntityIDMask = EntityPolicyType::ID_Mask;
  inline static constexpr GenerationType GenerationMask = EntityPolicyType::Generation_Mask;
  inline static constexpr IDType InvalidEntity = EntityPolicyType::Entity_Invalid;

  public:
    explicit constexpr MEntity()
      : m_value(InvalidEntity)
    { }

    IDType GetID() const 
    { 
      return static_cast<IDType>(m_value) & EntityIDMask;
    }

    GenerationType GetGeneration() const
    {
      return static_cast<GenerationType>(m_value >> PopCount(EntityIDMask)) & GenerationMask;
    }

    static bool Equals(const MEntity& V1, const MEntity& V2)
    {
      return (V1.GetGeneration() == V2.GetGeneration()) && (V1.GetID() == V2.GetID());
    }

  private:
    EntityType m_value;
};

template<typename EntityPolicyType>
bool operator==(const MEntity<EntityPolicyType>& Lhs, const MEntity<EntityPolicyType>& Rhs)
{
  return MEntity<EntityPolicyType>::Equals(Lhs, Rhs);
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