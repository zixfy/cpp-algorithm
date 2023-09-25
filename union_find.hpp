//
// Created by wwww on 2023/9/24.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
#include <vector>
class UnionFind {
private:
    std::vector<std::size_t> _parents;
    std::size_t _rank;
public:
    explicit UnionFind(std::size_t n) : _rank{n}, _parents{} {
        _parents.reserve(n);
        for (std::size_t i = 0; i < n ; ++i)
            _parents.emplace_back(i);
    }

};
#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_UNION_FIND_HPP
