#include <stdio.h>
#include <stdlib.h>

// リストの要素を表す構造体
typedef struct tagListNode {
    struct tagListNode *prev;
    struct tagListNode *next;
    int data;
} ListNode;

int main(void) {
    int buf, sum;
    ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;

    firstnode = lastnode = NULL;

    do {
        printf("整数を入力してください(0を入力すると終了)");
        scanf("%d", &buf);

        if (buf) {
            // 新たなノードを生成
            newnode = (ListNode*)malloc(sizeof(ListNode));
            newnode->data = buf;
            newnode->next = NULL;

            if (lastnode != NULL) {
                //既にあるリストの末尾にnewnodeをつなげる
                lastnode->next = newnode;
                newnode->prev = lastnode;
                lastnode = newnode;
            } else {
                firstnode = lastnode = newnode;

                // 先頭ノードなのでprevは無い。
                newnode->prev = NULL;

            }
        }

    } while(buf != 0);


    // 合計値算出
    printf(" --入力されたのは以下の数です--\n");
    sum = 0;

    // 先頭 firstnode 　thisnodeがNULLでない限り続け、イテレートするときにnextから取り出す
    for (thisnode = firstnode; thisnode != NULL; thisnode = thisnode->next) {
        printf("%d\t", thisnode->data);
        sum += thisnode->data;
    }

    printf("\n---\n以上の数の合計値 %d　\n", sum);
    // 全リストのノードを削除
    for (thisnode = firstnode; thisnode != NULL;) {
        removenode = thisnode;
        thisnode = thisnode->next;
        free(removenode);
    }
    return EXIT_SUCCESS;
}
   
