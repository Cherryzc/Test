#include "MySort.h"
#include <queue>

using namespace std;

// ������,���öѻ������ѣ��������ݽṹ����Ƶ�һ�������㷨��
// O(nlogn)��ѡ�������һ�֡�ͬ���ǲ��ȶ������㷨
// 
// �ѷ�Ϊ�󶥶Ѻ�С���ѣ���ʵ������ȫ��������
// ����������ص���ٶ�λָ��������Ԫ�أ�root��1��ʼ��������ô�ӽڵ���������2���Ǹ��ڵ������
// �ѵĲ��������ѣ����루�������Ȼ���ϸ����������Ѷ��������ѵף�Ȼ���µĶѶ�Ԫ���³���
// 
// ���ľ��ǽ����󶥶ѣ�Ȼ����һ�����Ѷ�Ԫ��-��δ��������ĩβ


// ����һ������STL�����ȶ��� priority_queue ������ռ临�Ӷȣ�
// ���Կ� priority_queue Դ��ʵ�֣�vector + algorithm ��heap����
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

// ���������Լ�ʵ�ִ󶥶ѣ���һ����Ԫ�صķ�����ԭ�����Ͻ����󶥶ѡ����϶��¹���O(nlogn)����Ȼ�󵯳���ԭ����ĩβ
void check_bottom_up(int* arr, int nSize)
{
    //ĩβԪ�ص����²���Ԫ�أ�����Ƿ�Ҫ�ϸ�
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
    //����Ϊ�󶥶ѣ���һ���룬���϶��¹�����
    for (int i = 2; i <= nSize; i++)
    {
        check_bottom_up(arr, i);
    }
    //������ԭ����ĩβ�������
    for (int i = nSize-1; i > 0; i--)
    {
        // �����Ѷ�Ԫ�ص���β��Ȼ���³��Ѷ�����Ϊ�󶥶�
        std::swap(arr[0], arr[i]);
        heapDown(arr, i, 0);
    }

    PrintArr(arr, nSize);
}

//=======================================================================================

// ���������Լ�ʵ�ִ󶥶ѣ��� make_heap() ��ʵ�����ơ����¶��Ϲ���O(n)��, Ȼ�󵯳���ԭ����ĩβ 
// ����1���ײ���ʼ�����ǵ��򡿣����һ�����ڵ�����ɴ󶥶�
// ����2�����ϱ������и��ڵ㣬�����и��ڵ㶼���ò���1�ķ�����ֱ�����ڵ�
void HeapSort3(int* arr, int nSize)
{
    //����Ϊ�󶥶ѣ���һ���룬���¶��Ϲ�����
    for (int i = (nSize >> 1)-1 ; i >= 0; i--)
    {
        heapDown(arr, nSize, i);
    }

    //������ԭ����ĩβ�������
    for (int i = nSize - 1; i > 0; i--)
    {
        // �����Ѷ�Ԫ�ص���β��Ȼ���³��Ѷ�����Ϊ�󶥶�
        std::swap(arr[0], arr[i]);
        heapDown(arr, i, 0);
    }

    PrintArr(arr, nSize);
}