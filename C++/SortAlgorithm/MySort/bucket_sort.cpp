#include "MySort.h"
#include <vector>
#include <algorithm>

using namespace std;


// 桶排序，非比较排序算法。核心思想：也是分而治之的思想，一个范围内的数据n（大量数据更合适），放入到k个桶里（桶是有前提要求的，数据放进去时就是一个范围内，而且有顺序，比如桶k1里的数据<K2<k3...）
// 然后对每个桶的数据再排序，最后合并。所以也要找到合适的【桶-数据范围】映射关系，把数据放入正确的桶（而且最好每个桶能平均）

// 时间复杂度O(n+k)。当桶数量 k 比较大时，时间复杂度趋于O(n)。合并结果时需要遍历所有桶和元素，花费 O(n+k) 时间。
// 空间复杂度O(n+k)，需要借助 k 个桶和总共 n 个元素的额外空间
// 桶排序稳定性取决于 "排序桶内元素使用的算法" 是否稳定

void BucketSort(float* arr, int nSize)
{
    //我们的输入数据是 [0, 1)的小数，备注：使用小数举例子，比较简单找到桶索引和数据的映射关系
    
    int k = nSize / 2; // 申请总数据量一半数量的桶，预期就每个桶里2个数据

    vector<vector<float>> buckets(k);

    //遍历放入各个桶里
    for (int i = 0; i < nSize; ++i)
    {
        buckets[int(arr[i] * k)].push_back(arr[i]); //映射关系：因为是小数，所以数据和桶个数相乘正好落到对应桶的索引
    }

    for (int i = 0; i < k; ++i)
    {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    int index = 0;
    for (int i = 0; i < k; ++i)
    {
        for (float j : buckets[i])
        {
            arr[index++] = j;
        }
    }

    //打印结果
    for (int i = 0; i < nSize; i++)
    {
        cout << arr[i] << ",";
    }
    cout << endl;
}