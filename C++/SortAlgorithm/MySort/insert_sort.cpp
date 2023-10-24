#include "MySort.h"

using namespace std;


// �������򣺴ӵ�һ��Ԫ�ؿ�ʼ��������һ��������ǰ����������������
// ������Ļ�ÿ�ζ�Ҫ��ͷ�����ҳ������λ�á�
// ����Ļ��������붯����Ҫ���ƽ��Ԫ�أ���Ϊǰ�������������У����Է���������������к���Ԫ����һ�Աȣ���Ԫ��С�ͽ��������ﵽ�����Ч��
// O(n2) �����ȶ��������㷨

void InsertSort(int* arr, int nSize)
{
    for (int i = 1; i < nSize; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j-1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
            }
            else
            {
                break;
            }
        }
        PrintArr(arr, nSize);
    }

    PrintArr(arr, nSize);
}