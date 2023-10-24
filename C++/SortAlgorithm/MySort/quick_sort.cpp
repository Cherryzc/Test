#include "MySort.h"
#include <vector>

using namespace std;


// �������� ������ķ��η���ѡһ����׼Ԫ�أ�һ�˱����� ���бȻ�׼ֵС��Ԫ�ذڷ��ڻ�׼ǰ�棬���бȻ�׼ֵ���Ԫ�ذ��ڻ�׼�ĺ��棬Ȼ��ݹ���÷ֿ��������Ӵ�
// O(nlogn) ���ڲ��ȶ��������㷨


int sort_once(int* arr, int left, int right)
{
    int i = left;
    int j = right;
    int midValue = arr[left]; // �����Ż���׼����ѡȡ���ԣ���ֹ��ĳЩ�����µ�ʱ��Ч�ʱ�������������ʱ��ѡ�����Ϊ��׼�Ͳ����ˡ��������ѡȡ ���� ȡ�ס�β��������Ԫ�ص���λ����Ϊ��׼��
    while (i < j)
    {
        //���������ҵ�С�ڻ�׼ֵ��Ԫ��
        while (i < j && arr[j] >= midValue)
        {
            j--;
        }
        //���������ҵ����ڻ�׼ֵ��Ԫ��
        while (i < j && arr[i] <= midValue)
        {
            i++;
        }
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[i], arr[left]);
    return i;
}

// �ݹ�汾
void QuickSortInner(int* arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = sort_once(arr, left, right);

    // todo���Ż�ջ֡�ռ䣨β�ݹ��Ż��������������������н϶̵��Ǹ�ִ�еݹ�
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
// �ǵݹ�汾

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