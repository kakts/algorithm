#Compute number of turns when n is guaranteed to be in range
import sys

n, low, high = input().strip().split(' ')
n, low, high = [int(n), int(low), int(high)]

# Coplexity O(log(n))
def turns(n, low, high):
    turns = 0
    print(turns)
    # Continue while there is a potential number to guess
    while (high >= low):
        print("-----low", low)
        print("-----high", high)
        turns = turns + 1
        mid = (low + high) // 2
        if (mid == n):
            return turns
        elif (mid < n):
            low = mid + 1
        else:
            high = mid - 1

print(turns(n, low, high))
