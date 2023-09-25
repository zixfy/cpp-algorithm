//
// Created by wwww on 2023/9/24.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
#include <vector>
class UnionFind {
private:
    std::vector<std::size_t> _parents, _sizes;
    std::size_t _rank;
public:
    explicit UnionFind(std::size_t n) : _rank{n}, _parents{}, _sizes(n, 1) {
        _parents.reserve(n);
        for (std::size_t i = 0; i < n ; ++i)
            _parents.emplace_back(i);
    }

    // number of groups
    inline auto rank() {return _rank;}

    std::size_t find_parent(std::size_t x) {
        if (_parents[x] != x)
            return _parents[x] = find_parent(_parents[x]);
        return x;
    }

    inline auto has_same_group_of(std::size_t a, std::size_t b) {
        return find_parent(a) == find_parent(b);
    }

    // return if successfully merged
    inline auto unite(std::size_t a, std::size_t b) {
        auto pa = find_parent(a), pb = find_parent(b);
        if (pa == pb)
            return false;
        if (_sizes[pa] < _sizes[pb])
            std::swap(pa, pb);
        _parents[pb] = pa;
        _sizes[pb] += _sizes[pa];
        --_rank;
        return true;
    }
};
#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
