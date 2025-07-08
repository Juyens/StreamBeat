#pragma once

#include "List.h"

template<class T, class Compare = std::less<T>>
class MergeSort
{
public:
    static void sort(List<T>& list, Compare cmp = Compare())
    {
        if (list.size() <= 1)
            return;

        mergeSort(list, 0, list.size() - 1, cmp);
    }

private:
    static void mergeSort(List<T>& list, int left, int right, Compare cmp)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(list, left, mid, cmp);
        mergeSort(list, mid + 1, right, cmp);
        merge(list, left, mid, right, cmp);
    }

    static void merge(List<T>& list, int left, int mid, int right, Compare cmp)
    {
        const int n1 = mid - left + 1;
        const int n2 = right - mid;

        List<T> leftList, rightList;

        for (int i = 0; i < n1; ++i)
            leftList.push_back(list[left + i]);

        for (int j = 0; j < n2; ++j)
            rightList.push_back(list[mid + 1 + j]);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (!cmp(rightList[j], leftList[i]))
                list[k++] = std::move(leftList[i++]);
            else
                list[k++] = std::move(rightList[j++]);
        }

        while (i < n1)
            list[k++] = std::move(leftList[i++]);

        while (j < n2)
            list[k++] = std::move(rightList[j++]);
    }
};
