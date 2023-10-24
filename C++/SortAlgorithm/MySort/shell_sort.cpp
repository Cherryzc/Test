#include "MySort.h"

using namespace std;


// 希尔排序：插入排序的一种更高效改进版本。也称缩小增量排序
// 初始选定一个间隔量（比如n/2），把数组按间隔量分成多个组，对每组使用插入排序算法排序，
// 然后逐步缩小间隔量，重复上面的操作，当间隔量减至1时就是插入排序了，排完就有序了（原理就是：当数组基本有序时，插入排序的效率是很高的）
// O(nlogn) 属于不稳定的排序算法

void ShellSort(int* arr, int nSize)
{
    int gap = nSize >> 1;
    while (gap > 0)
    {
        for (int group = 0; group < gap; group++)
        {
            for (int i = group; i < nSize; i += gap)
            {
                for (int j = i; j > group; j -= gap)
                {
                    if (arr[j- gap] > arr[j])
                    {
                        std::swap(arr[j - gap], arr[j]);
                    }
                    else
                        break;
                }
            }
        }
        PrintArr(arr, nSize);
        //缩小间隔
        gap >>= 1;
    }

    PrintArr(arr, nSize);
}