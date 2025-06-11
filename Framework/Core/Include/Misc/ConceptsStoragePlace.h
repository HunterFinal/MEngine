#pragma once

#ifndef _ME_CORE_CONCEPTS_STORAGE_PLACE_
#define _ME_CORE_CONCEPTS_STORAGE_PLACE_

#include "Misc/CoreDefines.h"

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

    template<typename MoveAssignment>
    concept MoveAssignableConcept = requires(MoveAssignment Lhs, MoveAssignment&& Rhs)
    {
      requires true;
    };
  }
}

// 
#define CHAR_TYPE_CONCEPT CONCEPT_ADAPTER(MEngine::Concepts::CharTypeConcept)

#endif // CAN_USE_CONCEPT

// define this if use c++20 or higher version
// downgrade to typename if version is lower c++20
#if CAN_USE_CONCEPT
  #define CONCEPT_ADAPTER(ConceptType) ConceptType 
#else
  #define CONCEPT_ADAPTER(...) typename
#endif


#ifndef CONCEPT_ADAPTER
  
#endif // CONCEPT_ADAPTER

#endif // _ME_CORE_CONCEPTS_STORAGE_PLACE_