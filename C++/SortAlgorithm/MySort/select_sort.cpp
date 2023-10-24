#include "MySort.h"

using namespace std;

// ѡ������ÿ�α���ѡ�����ֵ��������Ȼ���δ���򲿷����һ������
// ��ð������죬�Ϳ��ڽ��������٣�һ�˱���������ֻ����һ��
// O(n2) ���ڲ��ȶ������㷨

void SelectSort(int* arr, int nSize)
{
    for (int round = 0; round < nSize; round++)
    {
        int nMax = 0;
        for (int i = 0; i < nSize - round; i++)
        {
            if (arr[i] > arr[nMax])
            {
                nMax = i;
            }
        }
        std::swap(arr[nMax], arr[nSize - round - 1]);


        PrintArr(arr, nSize);
    }
}