#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)

int binary_search(int x, int *a, int left, int right) {
    int mid;

    // 同じ要素が配列にあった場合に、配列のインデックスが一番小さいものを
    // 返すようにする
    while (left < right) {
        mid = (left + right) / 2;
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (a[left] == x) {
        return left;
    }
}


