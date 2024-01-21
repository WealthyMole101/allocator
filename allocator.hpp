#pragma once

#include <iostream>
#include <memory>
#include <cstring>

template <class T>
struct pool_allocator
{
    typedef T value_type;

    static int pos;
    static constexpr int size = sizeof(T) * 1000;
    static uint8_t data[size];

    pool_allocator () noexcept {}
    ~pool_allocator() {}

    template <class U> pool_allocator  (const pool_allocator <U>&) noexcept {}

    T* allocate (std::size_t n) {
        if (pos + n > size) {
            throw std::bad_alloc();
        }

        int cur = pos;
        pos += n;
        return reinterpret_cast<T*>(data) + cur;
    }

    void deallocate (T* p, std::size_t n) {}

    template< class U >
    struct rebind
    {
        typedef pool_allocator<U> other;
    };
};

template <typename T>
uint8_t pool_allocator<T>::data[size];

template <typename T>
int pool_allocator<T>::pos = 0;


template <class T, class U>
constexpr bool operator== (const pool_allocator<T>& a1, const pool_allocator<U>& a2) noexcept
{
    return true;
}

template <class T, class U>
constexpr bool operator!= (const pool_allocator<T>& a1, const pool_allocator<U>& a2) noexcept
{
    return false;
}
