//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ALGORITHM_CURRY_HPP
#define CPP_ALGORITHM_CURRY_HPP

#include <iostream>
#include <functional>
#include <string>

namespace {
    namespace detail {
        template<typename Return, typename Arg>
        auto curry_impl(std::function<Return(Arg)> f) {
            return f;
        }

        template<typename Return, typename Arg, typename... Args>
        auto curry_impl(std::function<Return(Arg, Args...)> f) {
            return [f](Arg &&arg) {
                return curry_impl(std::function([&f, &arg](Args &&... args) {
                    return f(std::forward<Arg>(arg), std::forward<Args>(args)...);
                }));
            };
        }
    } // namespace detail
} // namespace
template<typename RetT, typename... ArgsT>
auto Curry = [](std::function<RetT(ArgsT...)> func) {
    if constexpr (sizeof...(ArgsT) < 2)
        return func;
    else
        return detail::curry_impl<RetT, ArgsT...>(func);
};

#endif //CPP_ALGORITHM_CURRY_HPP
