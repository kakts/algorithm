#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)

/**
 * linear search algorithm using sentinel-value
 * @param x 探し出す値
 * @param *a 検索対象の配列
 * @param num 配列の要素数
 */
int linear_search(int x, int *a, int num) {
    int n = 0;
    int t;

    // 配列の最後の要素をxと入れ替え
    t = a[num - 1];
    a[num - 1] = x;

    // 値が見つかるまでループ
    // 番兵を用いることにより、nと配列長の比較をしなくてすむため、
    // 計算量が減る　番兵を使う理由
    // 配列の最後の要素にxを入れているため、nの値が配列長を超えることはない
    while (a[n] != x) {
        n++;
    }

    if (n < num - 1) {
        return n;
    }
    if (t == x) {
        return num;
    }

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
    return 0;
}
