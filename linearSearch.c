#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)

/**
 * @param x 探し出す値
 * @param *a 検索対象の配列
 * @param num 配列の要素数
 */
int linear_search(int x, int *a, int num) {

    int n = 0;

    while (n < num && a[n] != x) {
        n++;
    }

    if (n < num) {
        return n;
    }

    // 見つからなかった場合
    return NOT_FOUND;
}

int main(void) {
    int i, searchNum, r, array[N];
    
    
    srand((unsigned int)time(NULL));

    // 適当な配列を作る
    for (i = 0; i < N; i++) {
        array[i] = rand() % 20;
        printf("[%d]:%d ", i, array[i]);
    }

    printf("\n 探したい数字を入力してください: ");
    scanf("%d", &searchNum);

    r = linear_search(searchNum, array, N);

    if (r == NOT_FOUND) {
        printf("%dは見つかりません\n", searchNum);
    } else {
        printf("%dは%d番目にあります\n", searchNum, r);
    }

}
