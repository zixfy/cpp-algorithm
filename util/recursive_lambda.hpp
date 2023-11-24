//
// Created by zixfy on 2023/11/15.
//

#ifndef CPP_ALGORITHM_RECURSIVE_LAMBDA_HPP
#define CPP_ALGORITHM_RECURSIVE_LAMBDA_HPP
#include "utility"
auto RecursiveLambda = [](auto &&lam) {
  return [lam_impl = std::forward<decltype(lam)>(lam)](
             auto &&...args) -> decltype(auto) {
    return lam_impl(lam_impl, std::forward<decltype(args)>(args)...);
  };
};
#endif // CPP_ALGORITHM_RECURSIVE_LAMBDA_HPP
