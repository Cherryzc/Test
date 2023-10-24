#include "MySort.h"
#include <vector>

using namespace std;


// 快速排序 ，经典的分治法。选一个基准元素，一趟遍历后 所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准的后面，然后递归调用分开的两个子串
// O(nlogn) 属于不稳定的排序算法


int sort_once(int* arr, int left, int right)
{
    int i = left;
    int j = right;
    int midValue = arr[left]; // 可以优化基准数的选取策略，防止在某些输入下的时间效率变差，比如数组逆序时，选最左侧为基准就不好了。可以随机选取 或者 取首、尾、中三个元素的中位数作为基准数
    while (i < j)
    {
        //从右向左找到小于基准值的元素
        while (i < j && arr[j] >= midValue)
        {
            j--;
        }
        //从左向右找到大于基准值的元素
        while (i < j && arr[i] <= midValue)
        {
            i++;
        }
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[i], arr[left]);
    return i;
}

// 递归版本
void QuickSortInner(int* arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = sort_once(arr, left, right);

    // todo：优化栈帧空间（尾递归优化），仅对两个子数组中较短的那个执行递归
    QuickSortInner(arr, left, mid - 1);
    QuickSortInner(arr, mid + 1, right);
}

void QuickSort(int* arr, int nSize)
{
    int left = 0;
    int right = nSize - 1;
    QuickSortInner(arr, left, right);

    PrintArr(arr, nSize);
}


//=================================================================
// 
// 非递归版本

struct LR
{
    int left;
    int right;

    LR()
    {

    }
    LR(const int&& i, const int&& j)
    {
        left = i;
        right = j;
    }
};

void QuickSort2(int* arr, int nSize)
{
    vector<LR> vecSort;
    vecSort.emplace_back(0, nSize - 1);
    while (!vecSort.empty())
    {
        LR lr = vecSort.back();
        vecSort.erase(vecSort.end()-1);
        int mid = sort_once(arr, lr.left, lr.right);

        if (lr.left < mid - 1)
        {
            vecSort.emplace_back(std::move(lr.left), std::move(mid - 1));
        }
        if (mid + 1 < lr.right)
        {
            vecSort.emplace_back(std::move(mid + 1), std::move(lr.right));
        }
    }

    PrintArr(arr, nSize);
}