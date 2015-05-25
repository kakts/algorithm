#include <stdio.h>
#include <stdlib.h>
// 入力値を計算する
// 配列長をユーザに入力してもらう
int main(void) {
    int buf, sum, count, n, i;
    int *array;

    // 入力するデータの個数を最初にきて必要なメモリ確保
    printf("何個の数値を入力しますか");
    scanf("%d", &count);
    array = (int*)malloc(sizeof(int) * count);

    n = 0;
    do {
        printf("整数を入力してください(０をおすと終了):");
        scanf("%d", &buf);
        if (buf) {
            // 入力値を配列に詰めていく
            array[n] = buf;
            n++;
        }
    } while (buf != 0);

    // 合計値算出
    printf("--入力されたのは以下の数です--");
    for (sum = i = 0; i < n; i++) {
        printf("%d \t", array[i]);
        sum += array[i];
    }
    printf("\n ----\n 以上の数の合計値は%dです。\n", sum);
    
    // メモリ解放
    free(array);
    return EXIT_SUCCESS;
}

