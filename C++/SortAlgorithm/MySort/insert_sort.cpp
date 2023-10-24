#include "MySort.h"

using namespace std;


// 插入排序：从第一个元素开始向后遍历，一个个插入前面已有序的子序列里。
// 单链表的话每次都要从头遍历找出插入的位置。
// 数组的话，做插入动作就要向后平移元素，因为前面是有序子序列，所以反向遍历有序子序列和新元素逐一对比，新元素小就交换，来达到插入的效果
// O(n2) 属于稳定的排序算法

void InsertSort(int* arr, int nSize)
{
    for (int i = 1; i < nSize; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j-1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
            }
            else
            {
                break;
            }
        }
        PrintArr(arr, nSize);
    }

    PrintArr(arr, nSize);
}