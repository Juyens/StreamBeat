#pragma once

template <typename T>
class NodoAVL
{
public:
    T data;
    NodoAVL* left;
    NodoAVL* right;
    int height;

    NodoAVL(const T& value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
};
