//
// Created by wwww on 2023/9/24.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_SEGMENT_TREE_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_SEGMENT_TREE_HPP
#include "../template/concept.hpp"
#include <memory>
#include <vector>
template <Concept::IsArithmetic T> class SegmentTree {
  struct Node {
    std::size_t range_left, range_right;
    T lazy_base, min, max, sum;
    Node *left_child, *right_child;
    ~Node() {
      delete left_child;
      delete right_child;
    }
  };
  Node *_root;
  template <typename Iter>
  Node *_build(Iter begin, Iter end, std::size_t left, std::size_t right) {
    if (begin + 1 == end)
      return new Node{left, right, 0, *begin, *begin, *begin, nullptr, nullptr};
    auto middle_gap = (right - left) >> 1;
    auto p_left = _build(begin, begin + middle_gap, left, left + middle_gap);
    auto p_right = _build(begin + middle_gap, end, left + middle_gap, right);
    return new Node{left,
                    right,
                    T{},
                    std::min(p_left->min, p_right->min),
                    std::max(p_left->max, p_right->max),
                    p_left->sum + p_right->sum,
                    p_left,
                    p_right};
  }

  inline void _update(Node *cur, T lazy) {
    cur->lazy_base += lazy;
    cur->min += lazy;
    cur->max += lazy;
    cur->sum += lazy * (cur->range_right - cur->range_left);
  }

  void _touch(Node *cur) {
    if (cur->lazy_base) {
      _update(cur->left_child, cur->lazy_base);
      _update(cur->right_child, cur->lazy_base);
      cur->lazy_base = {};
    }
  }

  T _range_sum(Node *cur, std::size_t left, std::size_t right) {
    auto r = std::min(right, cur->range_right);
    auto l = std::max(left, cur->range_left);
    if (l >= r)
      return {};
    if (r == cur->range_right && l == cur->range_left)
      return cur->sum;
    _touch(cur);
    return _range_sum(cur->left_child, left, right) +
           _range_sum(cur->right_child, left, right);
  }

  void _range_add(Node *cur, std::size_t left, std::size_t right, T increment) {
    auto r = std::min(right, cur->range_right);
    auto l = std::max(left, cur->range_left);
    if (l >= r)
      ;
    else if (r == cur->range_right && l == cur->range_left)
      _update(cur, increment);
    else {
      _touch(cur);
      _range_add(cur->left_child, left, right, increment);
      _range_add(cur->right_child, left, right, increment);
      cur->sum = cur->left_child->sum + cur->right_child->sum;
      cur->max = std::max(cur->left_child->max, cur->right_child->max);
      cur->min = std::max(cur->left_child->min, cur->right_child->min);
    }
  }

  T _range_min(Node *cur, std::size_t left, std::size_t right) {
    auto r = std::min(right, cur->range_right);
    auto l = std::max(left, cur->range_left);
    if (l >= r)
      return std::numeric_limits<T>::max();
    else if (r == cur->range_right && l == cur->range_left)
      return cur->min;
    _touch(cur);
    return std::min(_range_min(cur->left_child, left, right),
                    _range_min(cur->right_child, left, right));
  }

  T _range_max(Node *cur, std::size_t left, std::size_t right) {
    auto r = std::min(right, cur->range_right);
    auto l = std::max(left, cur->range_left);
    if (l >= r)
      return std::numeric_limits<T>::min();
    else if (r == cur->range_right && l == cur->range_left)
      return cur->max;
    _touch(cur);
    return std::max(_range_max(cur->left_child, left, right),
                    _range_max(cur->right_child, left, right));
  }

public:
  template <typename Iter>
  SegmentTree(Iter begin, Iter end)
    requires std::is_same_v<typename Iter::value_type, T>
      : _root{_build(begin, end, 0, std::size_t(std::distance(begin, end)))} {}

  ~SegmentTree() { delete _root; }

  inline T range_sum(std::size_t left, std::size_t right) {
    return _range_sum(_root, left, right);
  }

  inline void range_add(std::size_t left, std::size_t right, T increment) {
    _range_add(_root, left, right, increment);
  }

  inline T range_min(std::size_t left, std::size_t right) {
    return _range_min(_root, left, right);
  }

  inline T range_max(std::size_t left, std::size_t right) {
    return _range_max(_root, left, right);
  }
};
#endif // CPP_ADVANCED_CONTAINER_TEMPLATE_SEGMENT_TREE_HPP
