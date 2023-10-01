//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_PRIORITY_QUEUE_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_PRIORITY_QUEUE_HPP

#include <memory>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <optional>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
    using uz = std::size_t;
    std::vector<T> _vec;
    Compare _cmp;
    template<typename Container> using UniIter = std::conditional_t<
            std::is_rvalue_reference_v<Container>,
            std::move_iterator<typename std::decay_t<Container>::iterator>,
            typename std::decay_t<Container>::iterator>;
public:
    explicit PriorityQueue(Compare cmp = {}) : _vec{}, _cmp{cmp} {}

    template<typename Iterator>
    PriorityQueue(Iterator begin, Iterator end, Compare cmp = {}): _vec(begin, end),
                                                                   _cmp{cmp} { _maintain_from_chaos(); }

    PriorityQueue(std::initializer_list<T> il, Compare cmp = {}) : PriorityQueue(il.begin(), il.end(), cmp) {}

    template<typename Container>
    explicit
    PriorityQueue(Container &&container, Compare cmp = {}): PriorityQueue(
            UniIter<decltype(container)>(container.begin()), UniIter<decltype(container)>(container.end()), cmp) {}

    PriorityQueue(PriorityQueue const &) = default;

    PriorityQueue(PriorityQueue &&) noexcept = default;

    PriorityQueue &operator=(PriorityQueue const &) = default;

    PriorityQueue &operator=(PriorityQueue &&) noexcept = default;

    inline auto size() { return _vec.size(); }

    inline auto empty() { return _vec.empty(); }

    inline auto clear() { _vec.clear(); }

    T const &peek() {
        if (empty())
            throw std::runtime_error("peek on a empty PriorityQueue");
        return _vec.front();
    }

    inline T const *try_peek() {
        return empty() ? nullptr : _vec.front();
    }

    template<typename ForwardAsT = T>
    void push(ForwardAsT &&value) {
        _vec.push_back(std::forward<ForwardAsT>(value));
        _maintain_up(_vec.size() - 1);
    }

    template<typename ...Args>
    void emplace(Args ...args) {
        _vec.emplace_back(std::forward<Args>(args)...);
        _maintain_up(_vec.size() - 1);
    }

    T pop() {
        if (empty())
            throw std::runtime_error("pop on a empty PriorityQueue");
        std::swap(_vec.front(), _vec.back());
        auto ret = std::move(_vec.back());
        _vec.pop_back();
        _maintain_down(0);
        if (_vec.size() > 32 && _vec.size() * 2 < _vec.capacity())
            _vec.shrink_to_fit();
        return ret;
    }

    inline std::optional<T> try_pop() {
        return empty() ? std::optional<T>{} : pop();
    }

private:
    inline auto _father_of(uz x) {
        return (x - 1) >> 1;
    }

    inline auto _left_of(uz x) {
        return (x << 1) | 1;
    }


    void _maintain_up(uz current) {
        while (current != 0) {
            auto father = _father_of(current);
            if (_cmp(_vec[father], _vec[current]))
                std::swap(_vec[father], _vec[current]);
                // if father < current , let current grow
            else break;
            current = father;
        }
    }

    void _maintain_down(uz current) {
        for (auto child = _left_of(current); child < _vec.size(); child = _left_of(current)) {
            // while there is still any children for current node
            if (auto sibling = child + 1; sibling < _vec.size() && _cmp(_vec[child], _vec[sibling]))
                child = sibling;
            // select biggest child
            if (_cmp(_vec[current], _vec[child]))
                std::swap(_vec[current], _vec[child]);
                // if current  < child, let child grow
            else break;

            current = child;

        }
    }

    inline void _maintain_from_chaos() {
        for (uz i = _vec.size(); i > 0;)
            _maintain_down(--i);
    }
};

#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_PRIORITY_QUEUE_HPP
