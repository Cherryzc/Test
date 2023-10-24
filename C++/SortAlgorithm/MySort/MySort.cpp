// MySort.cpp: 定义应用程序的入口点。
//

#include "MySort.h"

using namespace std;

void PrintArr(int* arr, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		cout << arr[i] << ",";
	}
	cout << endl;
}

int main()
{
	int arr[9] = { 3, 6, 1, 5, 2, 9, 7, 4, 8 };

    cout << "ori:" << endl;;
    PrintArr(arr, 9);

	//BubbleSort(arr, 9);
	//SelectSort(arr, 9);
	//HeapSort3(arr, 9);
	//QuickSort2(arr, 9);
	//InsertSort(arr, 9);
	ShellSort(arr, 9);
	
	cout << "sort:" << endl;;
	PrintArr(arr, 9);
	return 0;
}
