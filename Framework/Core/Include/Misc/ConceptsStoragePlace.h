#pragma once

#ifndef _ME_CORE_CONCEPTS_STORAGE_PLACE_
#define _ME_CORE_CONCEPTS_STORAGE_PLACE_

#include "CoreDefines.h"

#if CAN_USE_CONCEPT

#include "Templates/IsCharTypeTraits.h"

// c++ standard concepts
#include <concepts>
#include <type_traits>

namespace MEngine
{

namespace Concepts
{
  template<typename CharType>
  concept CharTypeConcept = requires
  {
    requires MEngine::TypeTraits::IsCharType_V<CharType>;
  };

  template<typename EnumType>
  concept EnumTypeConcept = requires
  {
    requires std::is_enum_v<EnumType>;
  };

  template<typename FloatingType>
  concept FloatingTypeConcept = requires
  {
    requires std::is_floating_point_v<FloatingType>;
  };

  template<typename ArithmeticType>
  concept ArithmeticTypeConcept = requires
  {
    requires std::is_arithmetic_v<ArithmeticType>;
  };

  /**
   * Allocator concept
   * Avoid types: void  
   *              incompleted type
   */
  template<typename ElementType>
  concept AllocatorConcept = sizeof(ElementType) > 0;

} // namespace MEngine::Concepts

} // namespace MEngine

#define Requires_Derived_From(DerivedType, BaseType) requires std::derived_from<DerivedType, BaseType>

#endif // CAN_USE_CONCEPT

// Concept type define macro
#define CHAR_TYPE_CONCEPT                     CONCEPT_ADAPTER(MEngine::Concepts::CharTypeConcept)
#define ENUM_TYPE_CONCEPT                     CONCEPT_ADAPTER(MEngine::Concepts::EnumTypeConcept)
#define FLOATING_TYPE_CONCEPT                 CONCEPT_ADAPTER(MEngine::Concepts::FloatingTypeConcept)
#define ARITHMETIC_TYPE_CONCEPT               CONCEPT_ADAPTER(MEngine::Concepts::ArithmeticTypeConcept)
#define ALLOCATOR_TYPE_CONCEPT                CONCEPT_ADAPTER(MEngine::Concepts::AllocatorConcept)

#ifndef Requires_Derived_From
  #define Requires_Derived_From(...)
#endif

// define this if use c++20 or higher version
// downgrade to typename if version is lower c++20
#if CAN_USE_CONCEPT
  #define CONCEPT_ADAPTER(ConceptType) ConceptType 
  #define TEMPLATE_REQUIRES_DECLARATION(TemplateArgument, RequirementExpr) template < TemplateArgument > requires RequirementExpr
  #define TEMPLATE_REQUIRES_DEFINITION(TemplateArgument, RequirementExpr) TEMPLATE_REQUIRES_DECLARATION(TemplateArgument, RequirementExpr)
#else
  #define CONCEPT_ADAPTER(...) typename
  #define TEMPLATE_REQUIRES_DECLARATION(TemplateArgument, RequirementExpr) template < TemplateArgument, TEMPLATE_CONDITION_DECLARATION(RequirementExpr) >
  #define TEMPLATE_REQUIRES_DEFINITION(TemplateArgument, RequirementExpr) template < TemplateArgument, TEMPLATE_CONDITION_DEFINITION(RequirementExpr) >
#endif

#endif // _ME_CORE_CONCEPTS_STORAGE_PLACE_