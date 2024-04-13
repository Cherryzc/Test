// MySort.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。
void PrintArr(int* arr, int nSize);


// std::sort 基于我们熟悉的insertion sort, heap sort, quick sort. 1.检查容器元素数量，小于32则为插入排序, 2.当divisions数量达到限制（1.5 log2(N)）时，使用堆排序。3.否则，使用快速排序进行划分和部分递归。
// std::stable_sort 检查元素数量，小于32则为插入排序,如果大于32则进行归并排序
// std::partial_sort 可以对序列进行部分排序。它使用快速排序或堆排序，平均时间复杂度为O(n log n)。注意，std::partial_sort() 不保证稳定性。

void BubbleSort(int *arr, int nSize);

void SelectSort(int* arr, int nSize);
void HeapSort(int* arr, int nSize);
void HeapSort2(int* arr, int nSize);
void HeapSort3(int* arr, int nSize);

void QuickSort(int* arr, int nSize);
void QuickSort2(int* arr, int nSize);


void InsertSort(int* arr, int nSize);
void ShellSort(int* arr, int nSize);

void MergeSort(int* arr, int nSize);

//上面都是基于比较的排序算法，时间复杂度无法超越O(nlogn)
//下面的是非比较排序算法（需要额外空间），时间复杂度可以达到线性

void BucketSort(float* arr, int nSize); //桶排序
void CountingSort(int* arr, int nSize); // 计数排序
void RadixSort(int* arr, int nSize); // 基数排序