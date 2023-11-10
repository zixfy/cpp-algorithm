//
// Created by zixfy on 2023/10/26.
//

#ifndef CPP_ALGORITHM_CONTAINER_PRINTER_HPP
#define CPP_ALGORITHM_CONTAINER_PRINTER_HPP
#include "array"
#include "deque"
#include "format"
#include "forward_list"
#include "iostream"
#include "list"
#include "map"
#include "set"
#include "unordered_map"
#include "unordered_set"
#include "vector"
namespace DebugPrint {
namespace Literal {
using LiteralStr = const char[];
constexpr LiteralStr static array = "array", vector = "vector", deque = "deque",
                            list = "list", forward_list = "forward_list",
                            set = "set", unordered_set = "unordered_set",
                            multiset = "multiset",
                            unordered_multiset = "unordered_multiset",
                            map = "map", unordered_map = "unordered_map",
                            multimap = "multimap",
                            unordered_multimap = "unordered_multimap";
}; // namespace Literal

namespace ContainerType {
struct Seq {};
struct Map {};
struct Set {};
struct None {};
} // namespace ContainerType
template <const char S[]> struct DisplayName {
  constexpr static std::string_view value = S;
};

template <typename> struct stl_container_trait : ContainerType::None {};

template <typename T, size_t N>
struct stl_container_trait<std::array<T, N>> : ContainerType::Seq,
                                               DisplayName<Literal::array> {};

template <typename... P>
struct stl_container_trait<std::vector<P...>> : ContainerType::Seq,
                                                DisplayName<Literal::vector> {};

template <typename... P>
struct stl_container_trait<std::deque<P...>> : ContainerType::Seq,
                                               DisplayName<Literal::deque> {};

template <typename... P>
struct stl_container_trait<std::list<P...>> : ContainerType::Seq,
                                              DisplayName<Literal::list> {};

template <typename... P>
struct stl_container_trait<std::forward_list<P...>>
    : ContainerType::Seq, DisplayName<Literal::forward_list> {};

template <typename... P>
struct stl_container_trait<std::set<P...>> : ContainerType::Set,
                                             DisplayName<Literal::set> {};

template <typename... P>
struct stl_container_trait<std::unordered_set<P...>>
    : ContainerType::Set, DisplayName<Literal::unordered_set> {};

template <typename... P>
struct stl_container_trait<std::multiset<P...>>
    : ContainerType::Set, DisplayName<Literal::multiset> {};

template <typename... P>
struct stl_container_trait<std::unordered_multiset<P...>>
    : ContainerType::Set, DisplayName<Literal::unordered_multiset> {};

template <typename... P>
struct stl_container_trait<std::map<P...>> : ContainerType::Map,
                                             DisplayName<Literal::map> {};

template <typename... P>
struct stl_container_trait<std::unordered_map<P...>>
    : ContainerType::Map, DisplayName<Literal::unordered_map> {};

template <typename... P>
struct stl_container_trait<std::multimap<P...>>
    : ContainerType::Map, DisplayName<Literal::multimap> {};

template <typename... P>
struct stl_container_trait<std::unordered_multimap<P...>>
    : ContainerType::Map, DisplayName<Literal::unordered_multimap> {};

template <typename T>
concept IsSTLContainer =
    not std::is_base_of_v<ContainerType::None, stl_container_trait<T>>;

template <std::size_t N> consteval auto make_indent_char_array() {
  auto result = std::array<char, N>{};
  result.fill('\t');
  return result;
}

template <std::size_t N> struct indent {
  constexpr std::array<char, N> static char_arr = make_indent_char_array<N>();
  constexpr std::string_view static str = {char_arr.data(), char_arr.size()};
};

template <IsSTLContainer Container, std::size_t Depth = 0>
std::ostream &operator<<(std::ostream &os, Container const &container) {
  os << stl_container_trait<Container>::DisplayName::value << " [";

  using ElementT = typename Container::value_type;

  if constexpr (std::is_base_of_v<ContainerType::Map,
                                  stl_container_trait<Container>>) {
    using MappedT = typename ElementT::second_type;
    if constexpr (IsSTLContainer<MappedT>) {
      for (auto const &element : container)
        os << '\n'
           << indent<Depth + 1>::str << element.first << " : ",
            DebugPrint::operator<< <MappedT, Depth + 1>(os, element.second);
      os << '\n';
      if constexpr (Depth > 0)
        os << indent<Depth>::str;
    } else
      for (auto iter = container.cbegin(); iter != container.cend(); ++iter) {
        if (iter != container.cbegin())
          os << ", ";
        os << '{' << iter->first << " : " << iter->second << '}';
      }
  }

  else if constexpr (IsSTLContainer<ElementT>) {
    for (auto const &element : container)
      os << '\n'
         << indent<Depth + 1>::str,
          DebugPrint::operator<< <ElementT, Depth + 1>(os, element);
    os << '\n';
    if constexpr (Depth > 0)
      os << indent<Depth>::str;
  }

  else
    for (auto iter = container.cbegin(); iter != container.cend(); ++iter) {
      if (iter != container.cbegin())
        os << ", ";
      os << *iter;
    }
  return os << ']';
};
} // namespace DebugPrint
#endif // CPP_ALGORITHM_CONTAINER_PRINTER_HPP
