#include "MySort.h"

using namespace std;

// 冒泡排序，每次遍历，对比每两个元素，如果顺序不对就直接交换，这样一次遍历结束，最大值就交换到未排序部分最后一个了
// O(n2)属于稳定的排序算法

void BubbleSort(int* arr, int nSize)
{
    for (int round = 1; round < nSize; round++)
    {
        bool bSwap = false;
        for (int i = 0; i < nSize - round; i++)
        {
            if (arr[i] > arr[i+1])
            {
                std::swap(arr[i], arr[i + 1]);
                bSwap = true;
            }
        }
        if (!bSwap)
        {
            break; //已经有序直接结束
        }
        PrintArr(arr, nSize);
    }
}