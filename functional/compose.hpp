//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ALGORITHM_COMPOSE_HPP
#define CPP_ALGORITHM_COMPOSE_HPP
#include <functional>
#include <tuple>
#include <utility>
namespace {
template <std::size_t Index, typename... Func>
decltype(auto) compose_impl(std::tuple<Func...> &funcs) {
  if constexpr (Index + 1 == sizeof...(Func))
    return std::get<Index>(funcs);
  else
    return [&funcs, follow_func = compose_impl<Index + 1, Func...>(funcs)](
               auto &&...args) -> decltype(auto) {
      using ReturnT = std::invoke_result_t<decltype(std::get<Index>(funcs)),
                                           decltype(args)...>;
      if constexpr (std::is_void_v<ReturnT>) {
        std::get<Index>(funcs)(std::forward<decltype(args)>(args)...);
        return follow_func();
      } else
        return follow_func(
            std::get<Index>(funcs)(std::forward<decltype(args)>(args)...));
    };
}
template <typename... Func> struct Composer {
  std::tuple<Func...> funcs;
  using ComposedT = decltype(compose_impl<0, Func...>(funcs));
  ComposedT composed;
  template <typename... FuncRef>
  explicit Composer(FuncRef &&...f)
      : funcs{std::forward<FuncRef>(f)...},
        composed{compose_impl<0, Func...>(funcs)} {}
  template <typename... ArgT> decltype(auto) operator()(ArgT &&...args) {
    return composed(std::forward<ArgT>(args)...);
  }
};
}; // namespace

auto Compose = [](auto &&first_func, auto &&...other_func) -> decltype(auto) {
  if constexpr (sizeof...(other_func) == 0)
    return std::forward<decltype(first_func)>(first_func);
  else
    return Composer<std::remove_reference_t<decltype(first_func)>,
                    std::remove_reference_t<decltype(other_func)>...>(
        std::forward<decltype(first_func)>(first_func),
        std::forward<decltype(other_func)>(other_func)...);
};
#endif // CPP_ALGORITHM_COMPOSE_HPP

// using namespace std;
// struct A {
//   string name{"nihao"};
// };
// int main() {
//   A a;
//   std::function get_ref_to_my_name = [&]() -> string & { return a.name; };
//   std::function then_modify_it = [&](string &s) -> void {
//     s = "goodbye";
//     cout << "A::name set.\n";
//   };
//   std::function and_print = [&]() -> void {
//     cout << "A::name == \"" << a.name << "\" now\n";
//   };
//   auto &&action1 = Compose(get_ref_to_my_name, then_modify_it, and_print);
//   action1();
//   // output:
//   // A::name set.
//   // A::name == "goodbye" now
//
//   auto f1 = [](int a, int b) { return a + b; };
//   auto &&meaningless = Compose(f1);
//   // meaningless is lvalue reference to f1
//   static_assert(std::is_lvalue_reference_v<decltype(meaningless)>);
//
//   auto f2 = [](int x) -> double { return x * 1.16666666666666; };
//   auto &&action2 = Compose(
//       Compose(f1, f2), [](auto x) { return "Result: " + std::to_string(x);
//       });
//   cout << action2(-3, 5);
//   // output:
//   // Result: 2.333333
// }