#pragma once

using uint = unsigned int;

template <class T>
class BSNode
{
public:
    T data;
    BSNode* left = nullptr;
    BSNode* right = nullptr;

    BSNode() = default;

    explicit BSNode(const T& value)
        : data{ value } {}

    explicit BSNode(T&& value)
        : data{ std::move(value) } {}
};