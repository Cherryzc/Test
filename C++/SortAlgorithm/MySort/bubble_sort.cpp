#include "MySort.h"

using namespace std;

// ð������ÿ�α������Ա�ÿ����Ԫ�أ����˳�򲻶Ծ�ֱ�ӽ���������һ�α������������ֵ�ͽ�����δ���򲿷����һ����
// O(n2)�����ȶ��������㷨

void BubbleSort(int* arr, int nSize)
{
    for (int round = 1; round < nSize; round++)
    {
        bool bSwap = false;
        for (int i = 0; i < nSize - round; i++)
        {
            if (arr[i] > arr[i+1])
            {
                std::swap(arr[i], arr[i + 1]);
                bSwap = true;
            }
        }
        if (!bSwap)
        {
            break; //�Ѿ�����ֱ�ӽ���
        }
        PrintArr(arr, nSize);
    }
}