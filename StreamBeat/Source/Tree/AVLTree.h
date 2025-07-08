#pragma once

#include "NodoAVL.h"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>

template <typename T>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void insert(const T& value);
    void erase(const T& value);
    bool contains(const T& value) const;
    const T* find(const T& value) const;
    void clear();

    void inOrderTraversal() const;
    void inOrderTraversal(const std::function<void(const T&)>& callback) const;

private:
    NodoAVL<T>* root;

    void clear(NodoAVL<T>* node);
    void inOrderTraversal(NodoAVL<T>* node) const;

    int height(NodoAVL<T>* node) const;
    int balanceFactor(NodoAVL<T>* node) const;
    NodoAVL<T>* rotateRight(NodoAVL<T>* y);
    NodoAVL<T>* rotateLeft(NodoAVL<T>* x);
    NodoAVL<T>* balance(NodoAVL<T>* node);
    NodoAVL<T>* insert(NodoAVL<T>* node, const T& value);
    NodoAVL<T>* erase(NodoAVL<T>* node, const T& value);
    NodoAVL<T>* minValueNode(NodoAVL<T>* node) const;
};

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree()
{
    clear();
}

template <typename T>
int AVLTree<T>::height(NodoAVL<T>* node) const
{
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::balanceFactor(NodoAVL<T>* node) const
{
    return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
NodoAVL<T>* AVLTree<T>::rotateRight(NodoAVL<T>* y)
{
    NodoAVL<T>* x = y->left;
    NodoAVL<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename T>
NodoAVL<T>* AVLTree<T>::rotateLeft(NodoAVL<T>* x)
{
    NodoAVL<T>* y = x->right;
    NodoAVL<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

template <typename T>
NodoAVL<T>* AVLTree<T>::balance(NodoAVL<T>* node)
{
    if (balanceFactor(node) > 1)
    {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor(node) < -1)
    {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

template <typename T>
NodoAVL<T>* AVLTree<T>::insert(NodoAVL<T>* node, const T& value)
{
    if (!node)
        return new NodoAVL<T>(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    return balance(node);
}

template <typename T>
void AVLTree<T>::insert(const T& value)
{
    root = insert(root, value);
}

template <typename T>
NodoAVL<T>* AVLTree<T>::minValueNode(NodoAVL<T>* node) const
{
    NodoAVL<T>* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

template <typename T>
NodoAVL<T>* AVLTree<T>::erase(NodoAVL<T>* node, const T& value)
{
    if (!node)
        return node;

    if (value < node->data)
        node->left = erase(node->left, value);
    else if (value > node->data)
        node->right = erase(node->right, value);
    else
    {
        if (!node->left || !node->right)
        {
            NodoAVL<T>* temp = node->left ? node->left : node->right;
            if (!temp)
            {
                temp = node;
                node = nullptr;
            }
            else
                *node = *temp;
            delete temp;
        }
        else
        {
            NodoAVL<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = erase(node->right, temp->data);
        }
    }

    if (!node)
        return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    return balance(node);
}

template <typename T>
void AVLTree<T>::erase(const T& value)
{
    root = erase(root, value);
}

template <typename T>
bool AVLTree<T>::contains(const T& value) const
{
    NodoAVL<T>* current = root;
    while (current)
    {
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return true;
    }
    return false;
}

template <typename T>
const T* AVLTree<T>::find(const T& value) const
{
    NodoAVL<T>* current = root;
    while (current)
    {
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return &(current->data);
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::clear()
{
    clear(root);
    root = nullptr;
}

template <typename T>
void AVLTree<T>::clear(NodoAVL<T>* node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
void AVLTree<T>::inOrderTraversal() const
{
    inOrderTraversal(root);
}

template <typename T>
void AVLTree<T>::inOrderTraversal(NodoAVL<T>* node) const
{
    if (!node) return;
    inOrderTraversal(node->left);
    std::cout << node->data << " ";
    inOrderTraversal(node->right);
}

template <typename T>
void AVLTree<T>::inOrderTraversal(const std::function<void(const T&)>& callback) const
{
    std::function<void(NodoAVL<T>*)> traverse = [&] (NodoAVL<T>* node)
        {
            if (!node) return;
            traverse(node->left);
            callback(node->data);
            traverse(node->right);
        };

    traverse(root);
}
