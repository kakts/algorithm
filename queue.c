#include <stdio.h>
#define QUEUE_MAX (5 + 1) // キューのサイズ + 1
#define QUEUE_EMPTY -1

// 配列によるキュー構造
int queue[QUEUE_MAX];

// キューの先頭 (配列先頭からのオフセット)
int queue_first = 0;

// キューの末尾位置 (配列先頭からのオフセット)
int queue_last = 0;

// キューにデータを追加する
// 
// *リングバッファの考え方をもちいたキューの実装
// *キューの末尾にデータ格納
// *末尾ポインタを1つ進める
void enqueue(int val) {
    // lastの次がfirstの場合
    // (lastポインタ + 1) % QUEUE_MAX は次の配列の位置になる
    if((queue_last + 1) % QUEUE_MAX == queue_first) {
        // 現在配列の中身は、すべてキューの要素で埋まっている
        printf("ジョブが満杯です");
    } else {
        // キューに値を入れる
        queue[queue_last] = val;

        // queue_lastを1つ後ろにずらす
        // もし一番うしろの場合は先頭にもってくる
        queue_last = (queue_last + 1) % QUEUE_MAX;
   }
}

int dequeue(void) {
    int ret;

    // 配列に一つも要素がない時
    if(queue_first == queue_last) {
        return QUEUE_EMPTY;
    } else {
        // 一番先頭のキューを返す準備
        ret = queue[queue_first];

        // キューの先頭を次へ移動する
        queue_first = (queue_first + 1) % QUEUE_MAX;
        return ret;
   }
}

