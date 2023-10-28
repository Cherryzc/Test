#include "MySort.h"
#include <vector>

using namespace std;


// 计数排序：一般应用于“非负整数”数组（要排序的数据是整数，并不是说只适用于整数数组。比如一个对象里按其中一个整数成员变量排序）
// 核心思想：利用数组下标索引自然有序，找到输入数据的最大值m，然后申请一个 m+1 大小的辅助计数数组，遍历数据，索引对应m数组的值+1，这样就知道了一个数据出现的次数，同时大小顺序体现在m数组里了。
// 然后遍历m数组，计算“前缀和”（索引 i 处的前缀和等于数组前 i 个元素之和 .m[i] = m[i]+m[i-1]+m[i-2]+...+m[0]）
// 前缀和的意义：确定了一个数据在排序后数组 最大的索引位置（减一才是索引）。最后倒序遍历数据，根据计数数组就能知道 对应在结果数组的索引，放入结果数组，完成排序
// 适用于数据量大但数据范围较小的情况，要不然需要的 计数数组 m 太大

// 把辅助计数数组的索引看作一个桶（每个桶只能存一个元素），所以计数排序 可以看作是 桶排序在整数的一个特列

// 时间复杂度O(n+m),一般情况下 n远大于m ，时间复杂度趋于O(n)
// 空间复杂度O(n+m), 结果数组res 和 计数数组counter
// 稳定排序

void CountingSort(int* arr, int nSize)
{
    // 找到最大值
    int m = 0;
    for (int i = 0; i < nSize; ++i)
    {
        m = arr[i] > m ? arr[i] : m;
    }

    vector<int> counter(m + 1, 0);
    //计数
    for (int i = 0; i < nSize; ++i)
    {
        counter[arr[i]]++;
    }
    //计算前缀和
    for (int i = 1; i < m + 1; ++i)
    {
        counter[i] += counter[i - 1];
    }

    //倒序遍历数据，填充结果数组
    vector<int> res(nSize, 0);
    for (int i = nSize-1; i >= 0; --i)
    {
        int nIndex = counter[arr[i]]-- - 1;
        res[nIndex] = arr[i];
    }

    for (int i = 0; i < nSize; ++i)
    {
        arr[i] = res[i];
    }

    PrintArr(arr, nSize);
}