#include "MySort.h"
#include <queue>

using namespace std;

// 堆排序,利用堆积树（堆）这种数据结构所设计的一种排序算法，
// O(nlogn)是选择排序的一种。同样是不稳定排序算法
// 
// 堆分为大顶堆和小顶堆，其实就是完全二叉树。
// 利用数组的特点快速定位指定索引的元素，root从1开始计数，那么子节点索引除以2就是父节点的索引
// 堆的操作：建堆，插入（放入最后，然后上浮），弹出堆顶（换到堆底，然后新的堆顶元素下沉）
// 
// 核心就是建立大顶堆，然后逐一弹出堆顶元素-到未排序数组末尾


// 方案一：借助STL的优先队列 priority_queue （额外空间复杂度）
// 可以看 priority_queue 源码实现，vector + algorithm 的heap方法
void HeapSort(int* arr, int nSize)
{

//     priority_queue<int> pri_que;
//     for (int i = 0; i < nSize; i++)
//     {
//         pri_que.push(arr[i]);
//     }
    priority_queue<int> pri_que(arr, arr+9);
    for (int i = nSize - 1; i >= 0; i--)
    {
        arr[i] = pri_que.top();
        pri_que.pop();
    }

    PrintArr(arr, nSize);
}

//=======================================================================================

// 方案二：自己实现大顶堆，逐一插入元素的方法在原数组上建立大顶堆【自上而下构建O(nlogn)】，然后弹出到原数组末尾
void check_bottom_up(int* arr, int nSize)
{
    //末尾元素当作新插入元素，检查是否要上浮
    if (nSize < 2)
    {
        return;
    }

    int nCur = nSize - 1;
    int nParentPos = (nSize >> 1) - 1;
    while (nParentPos >= 0)
    {
        if (arr[nCur] > arr[nParentPos])
        {
            std::swap(arr[nCur], arr[nParentPos]);
            nCur = nParentPos;
        }
        
        if (nParentPos == 0)
        {
            break;
        }
        nParentPos--;
        nParentPos >>= 1;
    }
}
void heapDown(int* arr, int nSize, int top)
{
    if (nSize <= 0)
    {
        return;
    }
    
    int nParnet = top;
    while (1)
    {
        int nPosMax = nParnet;
        int lchild = 2 * nParnet + 1;
        int rchild = 2 * nParnet + 2;
        if (lchild < nSize && arr[lchild] > arr[nPosMax])
        {
            nPosMax = lchild;
        }
        if (rchild < nSize && arr[rchild] > arr[nPosMax])
        {
            nPosMax = rchild;
        }

        if (nPosMax == nParnet)
        {
            break;
        }
        std::swap(arr[nPosMax], arr[nParnet]);
        nParnet = nPosMax;
    }
}
void HeapSort2(int* arr, int nSize)
{
    //调整为大顶堆（逐一插入，自上而下构建）
    for (int i = 2; i <= nSize; i++)
    {
        check_bottom_up(arr, i);
    }
    //弹出到原数组末尾完成排序
    for (int i = nSize-1; i > 0; i--)
    {
        // 交换堆顶元素到结尾，然后下沉堆顶调整为大顶堆
        std::swap(arr[0], arr[i]);
        heapDown(arr, i, 0);
    }

    PrintArr(arr, nSize);
}

//=======================================================================================

// 方案三：自己实现大顶堆，和 make_heap() 的实现类似【自下而上构建O(n)】, 然后弹出到原数组末尾 
// 步骤1：底部开始【就是倒序】，最后一个父节点调整成大顶堆
// 步骤2：向上遍历所有父节点，对所有父节点都采用步骤1的方法，直到根节点
void HeapSort3(int* arr, int nSize)
{
    //调整为大顶堆（逐一插入，自下而上构建）
    for (int i = (nSize >> 1)-1 ; i >= 0; i--)
    {
        heapDown(arr, nSize, i);
    }

    //弹出到原数组末尾完成排序
    for (int i = nSize - 1; i > 0; i--)
    {
        // 交换堆顶元素到结尾，然后下沉堆顶调整为大顶堆
        std::swap(arr[0], arr[i]);
        heapDown(arr, i, 0);
    }

    PrintArr(arr, nSize);
}