#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* The number of Data */

int sort[N];

void BubbleSort(void) {
    int i, tmp, flag;

    do {
        flag = 0;
        for (i = 0; i < N - 1; i++) {
            // 第１要素からループして次の要素との大小比較
            if (sort[i] > sort[i + 1]) {
                flag = 1;
                tmp = sort[i];
                sort[i] = sort[i + 1];
                sort[i + 1] = tmp;
            }
        }
    } while (flag == 1);
}

int main(void) {
    int i;
    srand((unsigned int)time(NULL));

    printf("ソート準備:\n");
    for (i = 0; i < N; i++) {
        // ランダムな値を配列に格納
        sort[i] = rand();
        printf("%d \n", sort[i]);
    }

    printf("start sorting: \n");
    BubbleSort();

    printf("end sorting: \n");

    for (i = 0; i < N; i++) {
        printf("%d ", sort[i]);
    }

    return EXIT_SUCCESS;
}
