#include "MySort.h"
#include <vector>

using namespace std;


// �鲢����Ҳ�Ƿ��η���˼�룬�ȶ԰�ֳ��������������У�Ȼ��ݹ�����԰��ֱ�������鳤��Ϊ 1 ʱ���ٽ��кϲ��������������кϲ���һ�����������У����ϲ���������������


// ʱ�临�Ӷ� O(nlogn)
// �ռ临�Ӷ� O(n): �ݹ����Ϊ logn��ʹ�� O(logn) ��С��ջ֡�ռ�,�ϲ�������Ҫ������������ʵ�֣�ʹ�� O(n) ��С�Ķ���ռ�
// ����������������ʱ���Ը�Ϊ������ʽ��ʡȥ�ݹ�ʹ�õ�ջ֡�ռ䣬�鲢ʱ��������ϲ���Ҳ�������ռ䣬���Կռ临�Ӷȿ�����O(1)

// �ȶ�����

void merge(int* arr, int left, int mid, int right)
{
    // ���븨�������źϲ���������
    vector<int> m(right-left+1, 0);
    int il = left;
    int ir = mid + 1;
    int j = 0;
    //����������������һ�Աȴ�С
    while (il <= mid && ir <= right)
    {
        if (arr[il] <= arr[ir]) //��֤�ȶ��ԣ�������������
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
    // ����ʣ������
    while (il <= mid)
    {
        m[j++] = arr[il++]; //��������ʣ��
    }
    while (ir <= right)
    {
        m[j++] = arr[ir++]; //��������ʣ��
    }

    //���Ƶ�ԭ����
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