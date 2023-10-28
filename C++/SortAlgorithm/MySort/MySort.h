// MySort.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。
void PrintArr(int* arr, int nSize);

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