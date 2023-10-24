#希尔排序(Shell Sort)是插入排序的一种。也称缩小增量排序，是直接插入排序算法的一种更高效的改进版本。
#希尔排序是非稳定排序算法。该方法因DL．Shell于1959年提出而得名。 
# 初始选定一个间隔量（比如n/2），把数组按间隔量分成多个组，对每组使用插入排序算法排序，
# 然后逐步缩小间隔量，重复上面的操作，当间隔量减至1时就是插入排序了，排完就有序了（原理就是：当数组基本有序时，插入排序的效率是很高的）

def shell_sort(lists):
    #希尔排序
    count = len(lists)
    step = 2
    group = int(count / step)
    while group > 0:
        for i in range(0, group):
            j = i + group
            while j < count:
                k = j - group
                key = lists[j]
                while k >= 0:
                    if lists[k] > key:
                        lists[k + group] = lists[k]
                        lists[k] = key
                    k -= group
                j += group
        group /= step
        group = int(group)
    return lists

print(shell_sort([1, 4, 2, 3, 9, 6, 4]))
input("press <enter>")
