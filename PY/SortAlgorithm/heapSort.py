#堆排序(Heapsort)是指利用堆积树（堆）这种数据结构所设计的一种排序算法，
#它是选择排序的一种。
#可以利用数组的特点快速定位指定索引的元素。
#堆分为大根堆和小根堆，是完全二叉树。
#大根堆的要求是每个节点的值都不大于其父节点的值，即A[PARENT[i]] >= A[i]。
#在数组的非降序排序中，需要使用的就是大根堆，因为根据大根堆的要求可知，最大的值一定在堆顶。
#------------------------------------------------------------------------------------------

# 调整堆
def adjust_heap(lists, i, size):
    lchild = 2 * i + 1
    rchild = 2 * i + 2
    max = i
    if i < size / 2:
        if lchild < size and lists[lchild] > lists[max]:
            max = lchild
        if rchild < size and lists[rchild] > lists[max]:
            max = rchild
        if max != i:
            lists[max], lists[i] = lists[i], lists[max]
            adjust_heap(lists, max, size)

#创建堆
def build_heap(lists, size):
	for i in range(0, int(size/2))[::-1]:
		adjust_heap(lists, i, size)

def heap_sort(lists):
	#堆排序
	size = len(lists)
	build_heap(lists, size)
	for i in range(0, size)[::-1]:
		lists[0], lists[i] = lists[i], lists[0]
		adjust_heap(lists, 0, i)
	return lists

print(heap_sort([1, 4, 2, 3, 9, 6, 4]))
input("press <enter>")