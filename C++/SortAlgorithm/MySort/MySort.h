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