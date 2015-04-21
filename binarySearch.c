#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)

int binary_search(int x, int *a, int left, int right) {
    int mid;

    while(left <= right) {
        mid = (left + right) / 2;

        // 中間値の判定
        if(a[mid] == x) {
            return mid;
        }

        if(a[mid] < x) {
            // midより左側にxは存在しない
            left = mid + 1; 
        } else {
            right = mid - 1;
        }
    }

    //サーチ範囲が無くてもみつからない場合
    return NOT_FOUND;
}

int main(void) {
    int i, r, array[N];
    
    srand((unsigned int) time(NULL));
    
    for (i = 1; i < N; i++) {
        printf("[%d]:%d", i, array[i] = array[i-1] + rand() % 3);
    }

    scanf("%d", &i);
    
    r = binary_search(i, array, 0, N-1);

    if (r == NOT_FOUND) {
        printf("%d is not found\n", i);
    } else {
        printf("%d is : %d", i, r);
    }

    return EXIT_SUCCESS;
}
