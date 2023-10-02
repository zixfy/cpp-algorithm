//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ALGORITHM_COMPOSE_HPP
#define CPP_ALGORITHM_COMPOSE_HPP
#include <utility>
namespace {
template<typename Func, typename ...OtherFunc>
decltype(auto) compose_impl(Func const &f, OtherFunc const &...oth) {
    if constexpr (sizeof...(oth) == 0)
        return f;
    else
        return [&](auto &&...args) -> decltype(auto) {
            return compose_impl(oth...)(f(std::forward<decltype(args)>(args)...));
        };
}
};

auto Compose = [](auto &&f, auto &&...oth) -> decltype(auto) {
    if constexpr (sizeof...(oth) == 0)
        return std::forward<decltype(f)>(f);
    else
        return [f = std::forward<decltype(f)>(f), ...oth = std::forward<decltype(oth)>(oth)](auto &&...args) {
            return compose_impl(oth...)(f(std::forward<decltype(args)>(args)...));
        };
};
#endif //CPP_ALGORITHM_COMPOSE_HPP
