#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 初期配列のサイズ

// 配列自動拡張する
// 配列の要素がいっぱいになったら
// 初期配列の倍のサイズの配列を用意して新しく返す
int main(void) {
    int buf, sum, count, i;
    int n = 10;
    int *array, *temp;

    // 入力するデータの個数を最初にきて必要なメモリ確保
    array = (int*)malloc(sizeof(int) * n);

    count = 0;
    do {
        printf("整数を入力してください(０をおすと終了):");
        scanf("%d", &buf);
        if (buf) {
            // 入力値を配列に詰めていく
            array[count] = buf;
            count++;
        

            if (count == n) {
                printf("拡張");
                // 拡張
                temp = (int*)malloc(sizeof(int) * n * 2);
            
                // arrayの先頭から指定したバイト分、第１引数のメモリにコピー
                memcpy(temp, array, sizeof(int) * n);

                // 古い配列のメモリは解放する
                free(array);

                array = temp;

                // 配列長を２倍にする
                n *= 2;
            }
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

