//
// Created by wwww on 2023/10/6.
//

#ifndef CPP_ALGORITHM_TRAIT_ADAPTER_HPP
#define CPP_ALGORITHM_TRAIT_ADAPTER_HPP
// #include "template/unnamed.hpp"
// #include <iostream>
// #include <string>
// #include <tuple>
// #include <vector>
// using namespace std;
// struct Dyn;
// template <typename...> struct CanFly;
// template <typename Self> CanFly(Self &) -> CanFly<Self>;
//
// namespace Trait {
// template <typename Impl>
// concept CanFly = requires(Impl impl) {
//   { impl.fly() } -> same_as<void>;
// };
// } // namespace Trait
//
// template <> struct CanFly<Dyn> {
//   virtual void fly() = 0;
// };
//
// struct Bird {
//   string name;
// };
// template <> struct CanFly<Bird> : CanFly<Dyn> {
//   Bird &self;
//   CanFly(Bird &s) : self{s} {}
//   void fly() override { cout << self.name << " bird fly" << endl; }
// };
//
// struct Cow {
//   string name;
// };
//
// template <> struct CanFly<Cow> : CanFly<Dyn> {
//   Cow &self;
//   CanFly(Cow &s) : self{s} {}
//   void fly() { cout << self.name << ", also can fly" << endl; }
// };
//
// template <Trait::CanFly Trait> void just_fly(Trait t) { t.fly(); }
// int main() {
//   Bird b{"eagle"};
//   Cow n{"NB"};
//   CanFly fb{b};
//   CanFly fn{n};
//   std::move(fb).fly();
//   just_fly(fb);
//   just_fly(fn);
//   vector<CanFly<Dyn>*> v;
//   CanFly<Dyn> *dynF = &fb;
//   dynF->fly();
//   dynF = &fn;
//   std::move(*dynF).fly();
//   //    just_fly(n);
// }
#endif // CPP_ALGORITHM_TRAIT_ADAPTER_HPP
