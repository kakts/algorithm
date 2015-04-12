#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000 /* The number of Data */

int sort[N];

/**
 * 一回ループを行うごとに配列の後方要素はループ済みになっている
 * ループの回数を保持する変数 kを追加し、ループ回数を減らす
 */
void BubbleSort(void) {
    int i, tmp, flag;
    
    int k;
    do {
        flag = 0;
        for (i = 0; i < N - 1 - k; i++) {
            // 第１要素からループして次の要素との大小比較
            if (sort[i] > sort[i + 1]) {
                flag = 1;
                tmp = sort[i];
                sort[i] = sort[i + 1];
                sort[i + 1] = tmp;
            }
        }
        k++;
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
