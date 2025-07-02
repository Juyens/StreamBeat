#pragma once

#include "Node.h"

#include <iterator>

template<class T>
class Iterator 
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node<T>* node) : current(node) {}

    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }

    Iterator& operator++() 
    {
        if (current) current = current->next;
        return *this;
    }

    bool operator!=(const Iterator& other) const 
    {
        return current != other.current;
    }

private:
    Node<T>* current;
};