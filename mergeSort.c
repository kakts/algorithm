#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sort[N];
int buffer[N];


void MergeSort(int n, int x[]) {
    int i, j, k, m;
    if (n <= 1) {
        return;
    }

    // nの中間値計算
    m = n / 2;

    // ブロックを前半後半に分ける
    MergeSort(m, x); // 後半
    MergeSort(n - m, x + m);

    // マージ操作
    for (i = 0; i < m; i++) {
        buffer[i] = x[i];
    }

    j = m;
    i = k = 0;

    while(i < m && j < n) {

        // buffer[]とx[]の配列を比較していく
        // 両者の先頭要素を比較して小さい方を
        // x[]に順に詰めていく
        if (buffer[i] <= x[j]) {
            x[k++] = buffer[i++];
        } else {
            x[k++] = x[j++];
        }
    }
    
    while(i < m) {
        x[k++] = buffer[i++];
    }

}

int main(void) {
    int i;

    srand((unsigned int)time(NULL));

    for (i = 0; i < N; i++) {
        sort[i] = rand();
        printf("%d ", sort[i]);
    }

    printf("sort start\n");
    MergeSort(N, sort);
    printf("sort end\n");

    for (i = 0; i < N; i++){
        printf("%d \n", sort[i]);
    }

    return 0;
}
   

