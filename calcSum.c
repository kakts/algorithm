#include <stdio.h>
#include <stdlib.h>

#define NMAX 10

// 入力値を計算する
// 配列の数が10で固定なので、それ以上入力するとクラッシュする
int main(void) {
    int buf, sum, count, n;
    int array[NMAX];

    count = 0;
    do {
        printf("整数を入力してください(０をおすと終了):");
        scanf("%d", &buf);
        if (buf) {
            // 入力値を配列に詰めていく
            array[count] = buf;
            count++;
        }
    } while (buf != 0);

    // 合計値算出
    printf("--入力されたのは以下の数です--");
    for (sum = n = 0; n < count; n++) {
        printf("%d \t", array[n]);
        sum += array[n];
    }
    printf("\n ----\n 以上の数の合計値は%dです。\n", sum);
    return EXIT_SUCCESS;
}

