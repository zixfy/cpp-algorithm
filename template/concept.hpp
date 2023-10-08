//
// Created by wwww on 2023/10/7.
//

#ifndef CPP_ALGORITHM_CONCEPT_HPP
#define CPP_ALGORITHM_CONCEPT_HPP

#include <type_traits>
namespace Concept {
template <typename T> concept IsArithmetic = std::is_arithmetic_v<T>;
}
#endif // CPP_ALGORITHM_CONCEPT_HPP
