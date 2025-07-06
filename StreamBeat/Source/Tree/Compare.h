#pragma once

#include <memory>

template <typename T>
class CompareByName
{
public:
    bool operator()(const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) const
    {
        return a->getName() < b->getName();
    }
};