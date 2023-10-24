#include "MySort.h"

using namespace std;

// 选择排序，每次遍历选出最大值的索引，然后和未排序部分最后一个交换
// 比冒泡排序快，就快在交换操作少，一趟遍历结束后只交换一次
// O(n2) 属于不稳定排序算法

void SelectSort(int* arr, int nSize)
{
    for (int round = 0; round < nSize; round++)
    {
        int nMax = 0;
        for (int i = 0; i < nSize - round; i++)
        {
            if (arr[i] > arr[nMax])
            {
                nMax = i;
            }
        }
        std::swap(arr[nMax], arr[nSize - round - 1]);


        PrintArr(arr, nSize);
    }
}