#pragma once

#include "List.h"
#include <functional>
#include <vector>
#include <utility>

template<class T, class Compare = std::less<T>>
class MergeSort
{
public:
    static void sort(List<T>& list, Compare cmp = Compare())
    {
        if (list.size() <= 1)
            return;
        std::vector<T> vec(list.size());
        for (uint i = 0; i < list.size(); ++i)
            vec[i] = list[i];
        mergeSort(vec, 0, static_cast<int>(vec.size()) - 1, cmp);
        for (uint i = 0; i < vec.size(); ++i)
            list[i] = std::move(vec[i]);
    }

private:
    static void mergeSort(std::vector<T>& vec, int left, int right, Compare cmp)
    {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid, cmp);
        mergeSort(vec, mid + 1, right, cmp);
        merge(vec, left, mid, right, cmp);
    }

    static void merge(std::vector<T>& vec, int left, int mid, int right, Compare cmp)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<T> L(n1);
        std::vector<T> R(n2);
        for (int i = 0; i < n1; ++i)
            L[i] = vec[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = vec[mid + 1 + j];
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (!cmp(R[j], L[i]))
                vec[k++] = std::move(L[i++]);
            else
                vec[k++] = std::move(R[j++]);
        }
        while (i < n1)
            vec[k++] = std::move(L[i++]);
        while (j < n2)
            vec[k++] = std::move(R[j++]);
    }
};