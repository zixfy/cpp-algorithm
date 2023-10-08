//
// Created by wwww on 2023/10/4.
//

#ifndef CPP_ALGORITHM_VARIADIC_HPP
#define CPP_ALGORITHM_VARIADIC_HPP
#include <tuple>
#include <type_traits>
namespace Meta {
struct CantUnZipOddNumberOfVarTypes;
struct CantFindThatType;
template <typename... T> struct VarTypes;
template <class Cls> constexpr static inline bool IsVarTypes = false;
template <typename... T>
constexpr static inline bool IsVarTypes<VarTypes<T...>> = true;
template <typename... T> struct VarTypes {
  struct Impl {
    template <std::size_t I, typename U, typename... V> struct _Index {
      static_assert(I < 1 + sizeof...(V), "Range out of VarTypes");
      using type = _Index<I - 1, V...>::type;
    };
    template <typename U, typename... V> struct _Index<0, U, V...> {
      using type = U;
    };
    // Types = [T...] -> Types[I]

    struct _PopFront {
      template <typename First, typename... Oth> struct Helper {
        using type = VarTypes<Oth...>;
      };
      using type = Helper<T...>::type;
    }; // [T1, T2...] -> [T2...]

    struct _PopBack {
      template <typename First, typename... Oth> struct Helper {
        using type = Helper<Oth...>::type::template PushFront<First>;
      };
      template <typename Last> struct Helper<Last> {
        using type = VarTypes<>;
      };
      using type = Helper<T...>::type;
    }; // [T1..., T2] -> [T1...]

    template <std::size_t L, std::size_t R> struct _Slice {
      static_assert(L <= R && L < sizeof...(T) && R < sizeof...(T),
                    "Invalid Slice for VarTypes");
      template <std::size_t Cnt, typename U, typename... V> struct CutLeft {
        using type =
            typename CutLeft<Cnt - 1, V...>::type::template PushFront<U>;
      };
      template <typename U, typename... V> struct CutLeft<1, U, V...> {
        using type = VarTypes<U>;
      };
      template <typename U, typename... V> struct CutLeft<0, U, V...> {
        using type = VarTypes<>;
      };
      template <std::size_t Cnt, typename...> struct TrimLeft;
      template <std::size_t Cnt, typename U, typename... V>
      struct TrimLeft<Cnt, U, V...> {
        using type = typename TrimLeft<Cnt - 1, V...>::type;
      };
      template <typename U, typename... V> struct TrimLeft<0, U, V...> {
        using type = typename CutLeft<R - L, U, V...>::type;
      };
      using type = typename TrimLeft<L, T...>::type;
    }; // [L, R) sub-range in [U...]

    template <class Oth> struct _Concat {
      template <typename...> struct Helper;
      template <typename... U> struct Helper<VarTypes<U...>> {
        using type = VarTypes<T..., U...>;
      };
      using type = Helper<Oth>::type;
    }; // [T1, ...] , [T2, ...] -> [T1, ..., T2, ...]

    template <typename U, typename... V> struct _Reverse {
      using type = _Reverse<V...>::type::template PushBack<U>;
    };
    template <typename U> struct _Reverse<U> {
      using type = VarTypes<U>;
    };

    template <typename...> struct _Unzip;
    template <typename U, typename V, typename... W> struct _Unzip<U, V, W...> {
      using type =
          VarTypes<typename _Unzip<W...>::type::Front::template PushFront<U>,
                   typename _Unzip<W...>::type::Back::template PushFront<V>>;
    };
    template <> struct _Unzip<> {
      using type = VarTypes<VarTypes<>, VarTypes<>>;
    };
    template <typename U> struct _Unzip<U> {
      using type = VarTypes<VarTypes<>, VarTypes<>>;
    };
    // [U1, V1, U2, V2, ... , ] -> [U1, U2, ... , V1, V2]

    template <typename U> struct _Find {
      template <std::size_t Pivot, typename V, typename... W> struct Helper {
        constexpr inline static std::size_t value =
            std::is_same_v<U, V> ? Pivot : Helper<Pivot + 1, W...>::value;
      };
      template <std::size_t Pivot, typename Last> struct Helper<Pivot, Last> {
        constexpr inline static std::size_t value =
            std::is_same_v<U, Last> ? Pivot : Pivot + 1;
      };
      constexpr inline static std::size_t value = Helper<0, T...>::value;
    };

    template <class TT> struct _FromTuple {
      template <class TH> struct Helper;
      template <typename... U> struct Helper<std::tuple<U...>> {
        using type = VarTypes<U...>;
      };
      using type = Helper<TT>::type;
    };
  };
  static constexpr inline std::size_t Size = sizeof...(T);
  // length of [T...]

  template <std::size_t Position>
  using Index = Impl::template _Index<Position, T...>::type;
  // subscript I in list [U, V...]

  using Front = Impl::template _Index<0, T...>::type;
  using Back = Impl::template _Index<Size - 1, T...>::type;
  // Front / Back

  template <typename U> using PushBack = VarTypes<T..., U>;
  // push Type U in end of [T...]
  template <typename U> using PushFront = VarTypes<U, T...>;
  // [T...] -> [U, T...]

  using PopFront = Impl::_PopFront::type;
  // [T1, T2...] -> [T2...]
  using PopBack = Impl::_PopBack::type;
  // [T1..., T2] -> [T1...]

  template <std::size_t Left, std::size_t Right>
  using Slice = Impl::template _Slice<Left, Right>::type;
  // Types = [T...] -> Types[Left, Right)

  template <class Oth> using Concat = Impl::template _Concat<Oth>::type;
  // [T1, ...] , [T2, ...] -> [T1, ..., T2, ...]

  //  using Reverse = Impl::template _Reverse<T...>::type;

  using Unzip = typename Impl::template _Unzip<T...>::type;
  template <typename U>
  constexpr inline static std::size_t Find = Impl::template _Find<U>::value;
  // [T1, T2, T3, ..., Ti, ... TN] -> i

  using ToTuple = std::tuple<T...>;
  template <class TT> using FromTuple = Impl::template _FromTuple<TT>::type;
};

template <> struct VarTypes<> {
  static constexpr inline std::size_t Size = 0;
  using ToTuple = std::tuple<>;
  template <typename U> using PushFront = VarTypes<U>;
  template <typename U> using PushBack = VarTypes<U>;
};
} // namespace Meta
#endif // CPP_ALGORITHM_VARIADIC_HPP
