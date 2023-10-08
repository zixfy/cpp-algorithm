//
// Created by wwww on 2023/10/4.
//

#ifndef CPP_ALGORITHM_NAMED_TUPLE_HPP
#define CPP_ALGORITHM_NAMED_TUPLE_HPP
#include <tuple>
#include <iostream>
#include <string>
//using namespace std;
namespace {
template <typename U> struct UnPackPair;
template <typename U, typename V> struct UnPackPair<std::pair<U, V>> {
  using first = U;
  using second = V;
};
template <typename... NameAndTypes> struct DefineNamedTuple {
  using Tuple = std::tuple<typename UnPackPair<NameAndTypes>::second...>;
  template <typename T> struct Index_ {
    template <std::size_t I, typename U, typename... V> struct Helper {
      constexpr inline static std::size_t _v =
          std::is_same_v<T, typename UnPackPair<U>::first>
              ? I
              : Helper<I + 1, V...>::_v;
    };
    template <std::size_t I, typename U> struct Helper<I, U> {
      constexpr inline static std::size_t _v =
          std::is_same_v<T, typename UnPackPair<U>::first> ? I
                                                           : I + 1;
    };
    constexpr inline static std::size_t _v = Helper<0, NameAndTypes...>::_v;
  };
  template <typename T> constexpr inline static std::size_t At = Index_<T>::_v;
};
} // namespace

//namespace Named {
//template <typename U, typename V> using _ = std::pair<U, V>;
//namespace {
//struct name;
//struct address;
//struct age;
//struct id;
//struct master;
//}
//  using Person = DefineNamedTuple<
//    _<name, string>,
//    _<address, string>,
//    _<id, int>,
//    _<age, short>>;
//using Dog = DefineNamedTuple<
//    _<master, Person::Tuple>,
//    _<name, string>>;
//}
//int main() {
//  using namespace Named;
//  Person::Tuple t{"alice",  "CN", 114514, 17};
//  Dog::Tuple t2{t, "big black"};
//
//  cout << get<Person::At<name>>(t) << endl;
//  cout << get<Person::At<address>>(t) << endl;
//  cout << get<Person::At<age>>(t) << endl;
//  cout << get<Person::At<id>>(t) << endl;
//  cout << get<Dog::At<name>>(t2) << endl;
//  cout << get<Person::At<id>>(get<Dog::At<master>>(t2)) << endl;
//}
#endif // CPP_ALGORITHM_NAMED_TUPLE_HPP
