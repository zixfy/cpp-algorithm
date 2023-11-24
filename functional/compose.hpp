#ifndef CPP_ALGORITHM_COMPOSE_HPP
#define CPP_ALGORITHM_COMPOSE_HPP
#include <functional>
#include <type_traits>
namespace {
struct None {};
template <typename Arg, typename Func>
decltype(auto) operator|(Arg &&a, Func f) {
  using Ret = std::invoke_result_t<Func, decltype(a)>;
  if constexpr (std::is_void_v<Ret>) {
    f(a);
    return None{};
  } else
    return f(a);
}
template <typename Func> decltype(auto) operator|(None, Func f) {
  using Ret = std::invoke_result_t<Func>;
  if constexpr (std::is_void_v<Ret>) {
    f();
    return None{};
  } else
    return f();
}
} // namespace

template <typename... Func> struct Compose {
private:
  using FuncChain = std::tuple<Func...>;
  FuncChain funcs;
  template <std::size_t... Indexes, typename... ArgT>
  decltype(auto) _invoke(FuncChain &funcs,
                         std::integer_sequence<std::size_t, Indexes...>,
                         ArgT &&...args) {
    return (std::get<0>(funcs)(std::forward<ArgT>(args)...) | ... |
            std::get<Indexes + 1>(funcs));
  };

public:
  template <typename... FuncRef>
  explicit Compose(FuncRef &&...f) : funcs{std::forward<FuncRef>(f)...} {};
  template <typename... ArgT> decltype(auto) operator()(ArgT &&...args) {
    return _invoke(funcs, std::make_index_sequence<sizeof...(Func) - 1>{},
                   std::forward<ArgT>(args)...);
  }
};
template <typename... FuncRef>
Compose(FuncRef...) -> Compose<std::remove_reference_t<FuncRef>...>;

#endif // CPP_ALGORITHM_COMPOSE_HPP

// Another Recursive Implementation

// #ifndef CPP_ALGORITHM_COMPOSE_HPP
// #define CPP_ALGORITHM_COMPOSE_HPP
//
// #include <functional>
// #include <iostream>
// #include <string>
// #include <tuple>
// #include <utility>
// template <typename... Func> struct Compose {
// private:
//   using FuncChain = std::tuple<Func...>;
//   FuncChain funcs;
//
//   template <std::size_t Index, typename... ArgT>
//   decltype(auto) _invoke(FuncChain &funcs, ArgT &&...args) {
//     if constexpr (Index + 1 == sizeof...(Func))
//       return std::get<Index>(funcs)(std::forward<ArgT>(args)...);
//     else {
//       using CurrentResT = std::invoke_result_t<
//           std::remove_reference_t<decltype(std::get<Index>(funcs))>,
//           ArgT&&...>;
//       if constexpr (!std::is_void_v<CurrentResT>)
//         return _invoke<Index + 1, CurrentResT>(
//             funcs, std::get<Index>(funcs)(std::forward<ArgT>(args)...));
//       else {
//         std::get<Index>(funcs)(std::forward<ArgT>(args)...);
//         return _invoke<Index + 1>(funcs);
//       }
//     }
//   }
//
// public:
//   template <typename... FuncRef>
//   explicit Compose(FuncRef &&...f) : funcs{std::forward<FuncRef>(f)...} {};
//
//   template <typename... ArgT> decltype(auto) operator()(ArgT &&...args) {
//     return _invoke<0, ArgT...>(funcs, std::forward<ArgT>(args)...);
//   }
// };
// template <typename... FuncRef>
// Compose(FuncRef...) -> Compose<std::remove_reference_t<FuncRef>...>;
//
// #endif // CPP_ALGORITHM_COMPOSE_HPP