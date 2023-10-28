#include "MySort.h"
#include <vector>

using namespace std;


// 归并排序：也是分治法的思想，先对半分成左右两个子序列，然后递归继续对半分直到子数组长度为 1 时；再进行合并，把左右子序列合并成一个有序子序列，最后合并成完整有序序列


// 时间复杂度 O(nlogn)
// 空间复杂度 O(n): 递归深度为 logn，使用 O(logn) 大小的栈帧空间,合并操作需要借助辅助数组实现，使用 O(n) 大小的额外空间
// 更适用于链表，划分时可以改为迭代方式，省去递归使用的栈帧空间，归并时就是链表合并，也无需额外空间，所以空间复杂度可以是O(1)

// 稳定排序

void merge(int* arr, int left, int mid, int right)
{
    // 申请辅助数组存放合并后有序结果
    vector<int> m(right-left+1, 0);
    int il = left;
    int ir = mid + 1;
    int j = 0;
    //两个有序子序列逐一对比大小
    while (il <= mid && ir <= right)
    {
        if (arr[il] <= arr[ir]) //保证稳定性，优先左子序列
        {
            m[j] = arr[il];
            il++;
        }
        else if (arr[il] > arr[ir])
        {
            m[j] = arr[ir];
            ir++;
        }

        j++;
    }
    // 处理剩余的情况
    while (il <= mid)
    {
        m[j++] = arr[il++]; //左序列有剩余
    }
    while (ir <= right)
    {
        m[j++] = arr[ir++]; //右序列有剩余
    }

    //复制到原数组
    j = 0;
    for (int i = left; i <= right; ++i)
    {
        arr[i] = m[j++];
    }

}

void MergeSortInner(int* arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    MergeSortInner(arr, left, mid);
    MergeSortInner(arr, mid + 1, right);
    merge(arr, left, mid, right);

    PrintArr(arr, 9);
}

void MergeSort(int* arr, int nSize)
{
    int left = 0;
    int right = nSize - 1;
    MergeSortInner(arr, left, right);

    PrintArr(arr, nSize);
}