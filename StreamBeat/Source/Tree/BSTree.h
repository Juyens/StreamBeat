#pragma once

#include "BSNode.h"
#include "Compare.h"

#include <functional>
#include <utility>
#include <stdexcept>

using uint = unsigned int;

template <typename T, typename Compare = std::less<T>>
class BSTree
{
private:
    BSNode<T>* root_ = nullptr;
    Compare cmp_{};

    void insert(BSNode<T>*& node, const T& value)
    {
        if (!node)
        {
            node = new BSNode<T>(value);
        }
        else if (cmp_(value, node->data))
        {
            insert(node->left, value);
        }
        else
        {
            insert(node->right, value);
        }
    }

    void inOrder(BSNode<T>* node, const std::function<void(const T&)>& visit) const
    {
        if (!node) return;
        inOrder(node->left, visit);
        visit(node->data);
        inOrder(node->right, visit);
    }

    void destroy(BSNode<T>* node)
    {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BSTree() = default;

    BSTree(const BSTree&) = delete;
    BSTree& operator=(const BSTree&) = delete;

    BSTree(BSTree&& other) noexcept
        : root_(other.root_), cmp_(std::move(other.cmp_))
    {
        other.root_ = nullptr;
    }

    BSTree& operator=(BSTree&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            root_ = other.root_;
            cmp_ = std::move(other.cmp_);
            other.root_ = nullptr;
        }
        return *this;
    }

    ~BSTree()
    {
        clear();
    }

    void insert(const T& value)
    {
        insert(root_, value);
    }

    void inOrderTraversal(const std::function<void(const T&)>& visit) const
    {
        inOrder(root_, visit);
    }

    void clear()
    {
        destroy(root_);
        root_ = nullptr;
    }

    bool empty() const
    {
        return root_ == nullptr;
    }
};
