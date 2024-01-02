#pragma once

#include <iostream>
#include <memory>

//struct deleter
//{
//    void operator()(void* ptr)
//    {
//        ::operator delete(ptr);
//    }
//};

template <class T>
struct cpp_11_allocator {
    using value_type = T;

    cpp_11_allocator () noexcept
    {

    }

    template <class U> cpp_11_allocator(const cpp_11_allocator <U>& a) noexcept
    {

    }

    cpp_11_allocator select_on_container_copy_construction() const
    {
        std::cout << "cpp_11_allocator::select_on_container_copy_construction()" << std::endl;
        return cpp_11_allocator();
    }

    T* allocate (std::size_t n)
    {
        int a = sizeof(T);
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate (T* p, std::size_t n)
    {
        std::destroy_n(p, n);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args)
    {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    template<class U>
    struct rebind
    {
        typedef cpp_11_allocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type; //UB if std::false_type and a1 != a2;
};

template <class T, class U>
constexpr bool operator== (const cpp_11_allocator<T>& a1, const cpp_11_allocator<U>& a2) noexcept
{
    return true;
}

template <class T, class U>
constexpr bool operator!= (const cpp_11_allocator<T>& a1, const cpp_11_allocator<U>& a2) noexcept
{
    return false;
}
