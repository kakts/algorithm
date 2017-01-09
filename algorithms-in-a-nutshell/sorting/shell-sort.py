import sys

def shellSort(aList):
    subListCount = len(aList) // 2
    while subListCount > 0:
        for pos in range(subListCount):
            doGapInsertionSort(aList, pos, subListCount)

        print("After increments of size", subListCount);
        print("The list is", aList);

        subListCount = subListCount // 2

# 挿入ソート ギャップあり版
def doGapInsertionSort(aList, startPos, gap):
    for i in range(startPos + gap, len(aList), gap):
        currentVal = aList[i]
        position = i
        while position >= gap and aList[position - gap] > currentVal:
            aList[position] = aList[position - gap]
            position = position - gap

        aList[position] = currentVal

a = [int(a_temp) for a_temp in input().strip().split(' ')]
shellSort(a)
print(a)
