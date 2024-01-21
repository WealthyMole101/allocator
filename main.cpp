#include <iostream>
#include <map>

#include "allocator.hpp"
#include "container.hpp"

template <class T, class Allocator = std::allocator<T>>
void test_forward_list(ForwardList<T, Allocator>& forward_list)
{
//    forward_list.PushBack(505);
//    forward_list.PushBack(606);
//    forward_list.PushBack(707);

    for (int i = 0; i < 10; i++) {
        forward_list.PushBack(i);
    }

    for (int i = 0; i < forward_list.Size(); i++) {
        std::cout << forward_list.GetAt(i) << std::endl;
    }
}

int factorial(int i)
{
    if (i == 0) {
        return 1;
    } else {
        return i * factorial(i - 1);
    }
}

template <class T, class Allocator = std::allocator<T>>
void test_map(std::map<T, T, std::less<int>, Allocator> map_arg)
{
    for (int i = 0; i < 10; i++) {
        map_arg.insert({i, factorial(i)});
    }

    for (auto item: map_arg) {
        std::cout << item.first << " " << item.second << std::endl;
    }
}

int main (int, char **) 
{
    pool_allocator<int> allocator;
    ForwardList<int, pool_allocator<int>> forward_list_0(allocator);
    ForwardList<int> forward_list_1;

    std::map<int, int> map_0;
    pool_allocator<int> allocator_map;
    std::map<int, int, std::less<int>, pool_allocator<int>> map_1(allocator_map);

    test_forward_list(forward_list_0);
    test_forward_list(forward_list_1);

    test_map(map_0);
    test_map(map_1);

    return 0;
}
