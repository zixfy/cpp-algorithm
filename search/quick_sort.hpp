//
// Created by wwww on 2023/9/28.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
#include <random>
template <typename Iter, typename RandomEngineT = std::mt19937>
void quick_sort(Iter left, Iter right) {
    static std::random_device rd{};
    static RandomEngineT rng{rd()};
    auto length = std::distance(left, right);
    if (length < 2)
        return;
    // [l, r)
    auto base = *(left + rng() % length);
    auto iter1 = left, iter2 = right - 1;
    while (iter1 <= iter2) {
        if (*iter1 < base || (*iter1 == base && std::distance(left, iter1) < std::distance(iter2, right)))
            ++iter1;
        else
            std::swap(*iter1, *(iter2--));
    }
    quick_sort(left, iter1);
    quick_sort(iter2 + 1, right);
}
#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
