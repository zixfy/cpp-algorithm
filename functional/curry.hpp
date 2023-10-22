//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ALGORITHM_CURRY_HPP
#define CPP_ALGORITHM_CURRY_HPP

#include <functional>
#include <iostream>
#include <string>

namespace {
template <typename Return, typename Arg, typename... Args>
auto _curry_combine(std::function<Return(Arg, Args...)> original) {
  if constexpr (sizeof...(Args) == 0)
    return original;
  else
    return [f = std::move(original)](Arg &&arg) {
      return _curry_combine(std::function([&f, &arg](Args &&...args) {
        return f(std::forward<Arg>(arg), std::forward<Args>(args)...);
      }));
    };
}
} // namespace
template <typename RetT, typename... ArgsT>
auto Curry(std::function<RetT(ArgsT...)> func) {
  if constexpr (sizeof...(ArgsT) < 2)
    return func;
  else
    return _curry_combine<RetT, ArgsT...>(std::move(func));
};

template <typename FuncLike>
auto Curry(FuncLike&& func) {
  return Curry(std::function{std::forward<FuncLike>(func)});
};

#endif // CPP_ALGORITHM_CURRY_HPP
