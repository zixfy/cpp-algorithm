//
// Created by wwww on 2023/9/24.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_SEGMENT_TREE_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_SEGMENT_TREE_HPP
#include "../template/concept.hpp"
#include <memory>
#include <vector>
template <Concept::IsArithmetic T> class DynamicSegmentTree {
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

  inline void _update(Node *cur, T lazy) {
    cur->lazy_base += lazy;
    cur->min += lazy;
    cur->max += lazy;
    cur->sum += lazy * (cur->range_right - cur->range_left);
  }

  void _touch(Node *cur) {
    if (cur->left_child == nullptr) {
      auto middle =
          cur->range_left + ((cur->range_right - cur->range_left) >> 1);
      cur->left_child =
          new Node{cur->range_left,
                   middle,
                   T{},
                   cur->min,
                   cur->max,
                   cur->sum / (cur->range_right - cur->range_left) *
                       (middle - cur->range_left),
                   nullptr,
                   nullptr};
      cur->right_child =
          new Node{middle,
                   cur->range_right,
                   T{},
                   cur->min,
                   cur->max,
                   cur->sum / (cur->range_right - cur->range_left) *
                       (cur->range_right - middle),
                   nullptr,
                   nullptr};
      cur->lazy_base = {};
    } else if (cur->lazy_base) {
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
    else if (r == cur->range_right && l == cur->range_left) {
      _update(cur, increment);
    } else {
      _touch(cur);
      _range_add(cur->left_child, left, right, increment);
      _range_add(cur->right_child, left, right, increment);
      cur->sum = cur->left_child->sum + cur->right_child->sum;
      cur->max = std::max(cur->left_child->max, cur->right_child->max);
      cur->min = std::min(cur->left_child->min, cur->right_child->min);
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
  DynamicSegmentTree(std::size_t from, std::size_t to) : _root{new Node{from, to, T{}, T{}, T{}, T{}, nullptr, nullptr}} {
  }
  ~DynamicSegmentTree() {
    delete _root;
  }

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
#endif // CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_SEGMENT_TREE_HPP
