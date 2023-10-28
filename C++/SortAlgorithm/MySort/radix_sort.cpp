#include "MySort.h"
#include <vector>

using namespace std;


// �������������ָ�λ֮��ĵݽ���ϵ�����ζ�ÿһλ�������򣬴Ӷ��õ����յ��������������Կ����Ƕ�μ�������
// ����������������ֵ����̫�󣬷���ᵼ�¸�������������Ҫ��������ڴ�ռ䣬�������ֵ 10��10�η�

// ������ �����������ݷ�Χ������������������Ҫ���ڴ��ˣ��������ݱ�����Ա�ʾΪ�̶�λ���ĸ�ʽ����λ�����ܹ���

// ʱ�临�Ӷ� O(nk),k��λ�� ������k����̫��Ҫ�����ܳ���n2��
// �ռ临�Ӷ� O(n+m) ���ͼ�������һ��
// �ȶ�����



// ʮ����
int GetDigit(int value, int x) // x �� 1,10,100...
{
    return int(value / x) % 10;
}

void DigitCountingSort(int* arr, int nSize, int x)
{
    //ʮ���Ƶ�����������������size=10;
    vector<int> counter(10, 0);

    //����
    for (int i = 0; i < nSize; ++i)
    {
        counter[GetDigit(arr[i], x)]++;
    }
    //����ǰ׺��
    for (int i = 1; i < counter.size(); ++i)
    {
        counter[i] += counter[i-1];
    }
    //����������ݣ����������
    vector<int> res(nSize, 0);
    for (int i = nSize-1; i >= 0; --i)
    {
        int index = counter[GetDigit(arr[i], x)]-- - 1;
        res[index] = arr[i];
    }
    //���Ƶ�ԭ����
    for (int i = 0; i < nSize; ++i)
    {
        arr[i] = res[i];
    }
}

void RadixSort(int* arr, int nSize)
{
    // �ҵ����ֵ
    int m = 0;
    for (int i = 0; i < nSize; ++i)
    {
        m = arr[i] > m ? arr[i] : m;
    }

    // �Ӹ�λ��ʼ����λ���м�������
    for (int x = 1; x <= m; x *= 10)
    {
        DigitCountingSort(arr, nSize, x);
    }

    //��ӡ���
    for (int i = 0; i < nSize; i++)
    {
        cout << arr[i] << ",";
    }
    cout << endl;
}