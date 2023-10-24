#include "MySort.h"

using namespace std;


// ϣ�����򣺲��������һ�ָ���Ч�Ľ��汾��Ҳ����С��������
// ��ʼѡ��һ�������������n/2���������鰴������ֳɶ���飬��ÿ��ʹ�ò��������㷨����
// Ȼ������С��������ظ�����Ĳ����������������1ʱ���ǲ��������ˣ�����������ˣ�ԭ����ǣ��������������ʱ�����������Ч���Ǻܸߵģ�
// O(nlogn) ���ڲ��ȶ��������㷨

void ShellSort(int* arr, int nSize)
{
    int gap = nSize >> 1;
    while (gap > 0)
    {
        for (int group = 0; group < gap; group++)
        {
            for (int i = group; i < nSize; i += gap)
            {
                for (int j = i; j > group; j -= gap)
                {
                    if (arr[j- gap] > arr[j])
                    {
                        std::swap(arr[j - gap], arr[j]);
                    }
                    else
                        break;
                }
            }
        }
        PrintArr(arr, nSize);
        //��С���
        gap >>= 1;
    }

    PrintArr(arr, nSize);
}