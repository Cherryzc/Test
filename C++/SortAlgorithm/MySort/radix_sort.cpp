#include "MySort.h"
#include <vector>

using namespace std;


// 基数排序：用数字各位之间的递进关系，依次对每一位进行排序，从而得到最终的排序结果。（可以看作是多次计数排序）
// 计数排序的数据最大值不能太大，否则会导致辅助计数数组需要分配大量内存空间，比如最大值 10的10次方

// 适用于 数据量大，数据范围大的情况（计数排序需要大内存了），但数据必须可以表示为固定位数的格式，且位数不能过大

// 时间复杂度 O(nk),k是位数 （所以k不能太大，要不可能超过n2）
// 空间复杂度 O(n+m) ，和计数排序一样
// 稳定排序



// 十进制
int GetDigit(int value, int x) // x 是 1,10,100...
{
    return int(value / x) % 10;
}

void DigitCountingSort(int* arr, int nSize, int x)
{
    //十进制的树，辅助计数数组size=10;
    vector<int> counter(10, 0);

    //计数
    for (int i = 0; i < nSize; ++i)
    {
        counter[GetDigit(arr[i], x)]++;
    }
    //计算前缀和
    for (int i = 1; i < counter.size(); ++i)
    {
        counter[i] += counter[i-1];
    }
    //逆序遍历数据，填充结果数组
    vector<int> res(nSize, 0);
    for (int i = nSize-1; i >= 0; --i)
    {
        int index = counter[GetDigit(arr[i], x)]-- - 1;
        res[index] = arr[i];
    }
    //复制到原数组
    for (int i = 0; i < nSize; ++i)
    {
        arr[i] = res[i];
    }
}

void RadixSort(int* arr, int nSize)
{
    // 找到最大值
    int m = 0;
    for (int i = 0; i < nSize; ++i)
    {
        m = arr[i] > m ? arr[i] : m;
    }

    // 从个位开始，逐位进行计数排序
    for (int x = 1; x <= m; x *= 10)
    {
        DigitCountingSort(arr, nSize, x);
    }

    //打印结果
    for (int i = 0; i < nSize; i++)
    {
        cout << arr[i] << ",";
    }
    cout << endl;
}