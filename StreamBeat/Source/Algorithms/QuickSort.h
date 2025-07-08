#pragma once

#include "List.h"

template<class T, class Compare = std::less<T>>
class QuickSort
{
public:
    static void sort(List<T>& list, Compare cmp = Compare())
    {
        if (list.size() <= 1)
            return;

        quickSort(list, 0, list.size() - 1, cmp);
    }

private:
    static void quickSort(List<T>& list, int low, int high, Compare cmp)
    {
        if (low >= high)
            return;

        int p = partition(list, low, high, cmp);
        quickSort(list, low, p - 1, cmp);
        quickSort(list, p + 1, high, cmp);
    }

    static int partition(List<T>& list, int low, int high, Compare cmp)
    {
        T pivot = list[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
        {
            if (cmp(list[j], pivot))
            {
                ++i;
                list.swap(i, j);
            }
        }
        list.swap(i + 1, high);
        return i + 1;
    }
};