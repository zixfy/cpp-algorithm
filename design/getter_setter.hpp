//
// Created by wwww on 2023/10/1.
//

#ifndef CPP_ALGORITHM_GETTER_SETTER_HPP
#define CPP_ALGORITHM_GETTER_SETTER_HPP

#include <functional>


template<typename Getter, typename Setter>
class Field {
    Getter _get;
    Setter _set;
    using GetterResT = std::invoke_result_t<Getter>;
public:
    explicit Field(
            Getter getter = {},
            Setter setter = {}
    ) : _get{getter}, _set{setter} {}

    GetterResT get() { return _get(); }

    operator GetterResT() { return _get(); }

    template<typename Arg>
    Field &operator=(Arg &&arg) {
        _set(std::forward<Arg>(arg));
        return *this;
    }
};


#endif //CPP_ALGORITHM_GETTER_SETTER_HPP
