//
// Created by wwww on 2023/10/5.
//

#ifndef CPP_ALGORITHM_RANGE_HPP
#define CPP_ALGORITHM_RANGE_HPP
#include <type_traits>
template <typename T>
concept TraitCanBeRanged = requires(T a, T b) {
  requires std::is_default_constructible_v<T>;
  { a++ } -> std::same_as<T>;
  { a < b } -> std::same_as<bool>;
  { a > b } -> std::same_as<bool>;
  { a + b } -> std::same_as<T>;
};
template <TraitCanBeRanged T> class Range {
  T _from, _to, _step;
  struct iterator {
    T _target, _current;
    iterator &operator++() {}
    bool operator!=(iterator const &oth) { return _current != oth._cur; }
    T &operator*() { return _current; }
  };

public:
  Range(T from, T to, T step) : _from{from}, _to{to}, _step{step} {}
  Range(T from, T to) : Range(from, to, {}) { ++_step; }
  template <template <typename> typename Container> Container<T> to() {}
  template <template <typename> typename Container, typename Func>
  Container<T> to(Func f) {
    return {};
  }
};
#endif // CPP_ALGORITHM_RANGE_HPP
