#pragma once

#include <limits>
#include <cstring>
#include "allocator.hpp"

template<class T>
class ForwardListNode
{
public:
    T data;
    ForwardListNode* next;

    ForwardListNode(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

template <class T, class Allocator = std::allocator<T>>
class ForwardList
{
public:
    ForwardList()
    {
        _head = _tail = nullptr;
        _capacity = 0;
    };

    ForwardList(const Allocator& alloc)
    {
        _alloc = alloc;
        _capacity = 10;
        typename decltype(_alloc)::template rebind<ForwardListNode<T>>::other node_alloc;
        _head = std::allocator_traits<decltype(node_alloc)>::allocate(node_alloc, _capacity);
        _tail = _head;
    };

    ~ForwardList()
    {
        std::allocator_traits<decltype(_node_alloc)>::deallocate(_node_alloc, _head, _capacity);
    };

    void PopFront()
    {
        if (_size > 0) {
            auto free_node = _head;
            _head = _head->next;
            std::allocator_traits<decltype(_node_alloc)>::destroy(_node_alloc, _tail);
            _size--;
        }
    };

    void PushBack(const T& data)
    {
        if (_size == _capacity) {
            _capacity = _capacity * 2 + 1;
            auto new_nodes = std::allocator_traits<decltype(_node_alloc)>::allocate(_node_alloc, _capacity);

            if (_head == nullptr) {
                _head = new_nodes;
                _tail = new_nodes;
            } else {
                std::memcpy(new_nodes, _head, _size * sizeof(ForwardListNode<T>));
                std::swap(new_nodes, _head);
                std::allocator_traits<decltype(_node_alloc)>::deallocate(_node_alloc, new_nodes, _size); //TODO
            }
        }

        int node_size =  sizeof(ForwardListNode<T>);
        ForwardListNode<T>* tail_offset = _head + _size;

        std::allocator_traits<decltype(_node_alloc)>::construct(_node_alloc, tail_offset, data);
        _tail->next = tail_offset; // Двигаем next у предыдущей ноды.
        _tail = tail_offset;

        if (_size == 0) {
            _head = tail_offset;
            _head->next = nullptr;
        }

        if (_size > 0) {
            ForwardListNode<T>* cur = (_head + (_size - 1) * node_size);
            cur->next = tail_offset;
        }

        _size++;
    };

    T GetAt(int k)
    {
        if (k < 0) {
            return std::numeric_limits<int>::max();
        }

        ForwardListNode<T>* node = _head;
        int n = 0;
        while (node && n != k && node->next) {
            node = node->next;
            n++;
        }

        return (n == k) ? node->data : std::numeric_limits<int>::max();
    };

    int Size()
    {
        return _size;
    }

protected:
private:
    ForwardListNode<T> *_head;
    ForwardListNode<T> *_tail;
    std::size_t _size = 0;
    std::size_t _capacity = 10;

    Allocator _alloc;
    typename decltype(_alloc)::template rebind<ForwardListNode<T>>::other _node_alloc;
};
