//
// Created by wwww on 2023/9/9.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_BINARY_INDEX_TREE_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_BINARY_INDEX_TREE_HPP

#include <vector>

template <typename T> class BinaryIndexTree {
public:
  explicit BinaryIndexTree(const std::vector<T> &tree) {
    m_tree.resize(tree.size() + 1, T());
    for (std::size_t i = 1; i < m_tree.size(); ++i) {
      m_tree[i] += tree[i - 1];
      auto j = i + low_bit(i);
      if (j < m_tree.size())
        m_tree[j] += m_tree[i];
    }
  }

  BinaryIndexTree() : BinaryIndexTree(std::vector<T>{}) {}

  void add(std::size_t index, T value) {
    index += 1;
    while (index < m_tree.size()) { // 不能越界
      m_tree[index] += value;
      index += low_bit(index);
    }
  }

  inline T range_sum(std::size_t l, std::size_t r) {
    return get_prefix(r + 1) - get_prefix(l);
  }

  T get_prefix(std::size_t x) { // a[1]..a[x]的和
    T ans{};
    while (x > 0) {
      ans += m_tree[x];
      x -= low_bit(x);
    }
    return ans;
  }

private:
  std::vector<T> m_tree;

  inline std::size_t low_bit(std::size_t x) { return x & -x; }
};

#endif // CPP_ADVANCED_CONTAINER_TEMPLATE_BINARY_INDEX_TREE_HPP
