#pragma once

#include "List.h"
#include <functional>
#include <vector>
#include <utility>

template<class T, class Compare = std::less<T>>
class QuickSort
{
public:
    static void sort(List<T>& list, Compare cmp = Compare())
    {
        if (list.size() <= 1)
            return;
        std::vector<T> vec(list.size());
        for (uint i = 0; i < list.size(); ++i)
            vec[i] = list[i];
        quickSort(vec, 0, static_cast<int>(vec.size()) - 1, cmp);
        for (uint i = 0; i < vec.size(); ++i)
            list[i] = std::move(vec[i]);
    }

private:
    static void quickSort(std::vector<T>& vec, int low, int high, Compare cmp)
    {
        if (low >= high)
            return;
        int p = partition(vec, low, high, cmp);
        quickSort(vec, low, p - 1, cmp);
        quickSort(vec, p + 1, high, cmp);
    }

    static int partition(std::vector<T>& vec, int low, int high, Compare cmp)
    {
        T pivot = vec[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
        {
            if (cmp(vec[j], pivot))
            {
                ++i;
                std::swap(vec[i], vec[j]);
            }
        }
        std::swap(vec[i + 1], vec[high]);
        return i + 1;
    }
};