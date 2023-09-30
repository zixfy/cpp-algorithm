//
// Created by wwww on 2023/9/27.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_ARRAY_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_ARRAY_HPP

#include <memory>

template<typename T>
class DynamicArray {
    std::size_t _size;
    T *_ptr;

public:
    DynamicArray() = delete;

    DynamicArray(std::size_t size, const T &val) : _size{size}, _ptr{new T[size]} {
        std::fill(_ptr, _ptr + _size, val);
    }

    explicit DynamicArray(std::size_t size) : DynamicArray(size, T{}) {}

    ~DynamicArray() {
        delete[] _ptr;
    }

    DynamicArray(const DynamicArray &oth) : _size{oth._size}, _ptr{new T[oth._size]} {
        std::copy(oth._ptr, oth._ptr, _ptr);
    }

    DynamicArray(DynamicArray &&oth) noexcept: _size{oth._size}, _ptr{oth._ptr} {
        oth._ptr = nullptr;
        oth._size = 0;
    }

    DynamicArray &operator=(const DynamicArray &oth) {
        if (&oth == this)
            return *this;
        auto old = _ptr;
        _ptr = new T[oth.size()];
        std::copy(oth._ptr, oth._ptr, _ptr);
        _size = oth._size;
        delete old;
        return *this;
    }

    DynamicArray &operator=(DynamicArray &&oth) noexcept {
        if (&oth == this)
            return *this;
        auto old = _ptr;
        _ptr = oth._ptr;
        _size = oth._size;
        oth._ptr = nullptr;
        oth._size = 0;
        delete old;
        return *this;
    }

    inline T &operator[](std::size_t index) { return _ptr[index]; }

    inline const T &operator[](std::size_t index) const { return _ptr[index]; }

    inline auto size() const { return _size; }

    void copy_to(DynamicArray &oth, std::size_t index) {
        std::copy(_ptr, _ptr + _size, oth._ptr + index);
    }

    DynamicArray& concat(const DynamicArray& oth) {
        auto old=  _ptr;
        _ptr = new T[_size + oth._size];
        std::copy(old, old + _size, _ptr);
        std::copy(oth._ptr, oth._ptr + oth._size, _ptr + _size);
        _size += oth._size;
        delete old;
        return *this;
    }

    inline auto begin() { return _ptr; }

    inline auto end() { return _ptr + _size; }
};

#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_DYNAMIC_ARRAY_HPP
