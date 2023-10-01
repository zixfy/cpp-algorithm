//
// Created by wwww on 2023/9/28.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
#include <random>
template <typename Iter, typename Compare = std::less<typename Iter::value_type>, typename RandomEngineT = std::mt19937>
void quick_sort(Iter left, Iter right, Compare cmp = {}) {
    static std::random_device rd{};
    static RandomEngineT rng{rd()};
    auto length = std::distance(left, right);
    if (length < 2)
        return;
    if (length <= 10)
    {
        for (auto i = left; i != right; ++i)
            for (auto j = i + 1; j != right; ++j)
                if (cmp(*j, *i))
                    std::swap(*i, *j);
        return;
    }
    // [left, right)
    std::swap(*(left + rng() % length), *left);
    auto& base = *left;
    auto iter1 = left + 1, iter2 = right - 1;
    // [left, iter1), (iter2, right)
    while (iter1 <= iter2) {
        if (cmp(*iter1, base) || (!cmp(base, *iter1) && std::distance(left, iter1) < std::distance(iter2 + 1, right)))
            ++iter1;
        else
            std::swap(*iter1, *(iter2--));
    }
    quick_sort(left, iter1, cmp);
    quick_sort(iter2 + 1, right, cmp);
}
#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_QUICK_SORT_HPP
