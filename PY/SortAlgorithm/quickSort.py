#通过一趟排序将要排序的数据分割成独立的两部分，
#其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，
#整个排序过程可以递归进行，以此达到整个数据变成有序序列。(不稳定，但是可改造成稳定)

def quick_sort(lists, left, right):
    #快速排序
    if left >= right:
        return lists
    key = lists[left]
    low = left
    high = right
    while left < right:
        while left < right and lists[right] >= key:
            right -= 1
        lists[left] = lists[right]
        while left < right and lists[left] <= key:
            left += 1
        lists[right] = lists[left]
    lists[right] = key
    quick_sort(lists, low, left - 1)
    quick_sort(lists, left + 1, high)
    return lists
    
print(quick_sort([4, 1, 9, 5, 3, 7, 6], 0, 6))
input("press <enter>")
