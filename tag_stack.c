#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 括弧の種類
#define STAPLE_SMALL 1
#define STAPLE_MEDIUM 2
#define STAPLE_LARGE 3

// 1つの括弧を示す構造体
typedef struct _tagstaple {
    int line; // 括弧のある行
    int column; // 括弧のある列
    int type; // 括弧の種類

    // リスト形式でデータを持たせるので、前後のデータのポインタを持たせる
    struct _tagstaple *staple_next;
    struct _tagstaple *staple_prev;
} staple;

// リストによるスタック構造
// リストの先頭と最後尾を表すポインタ変数初期化
staple *staple_head = NULL;
staple *staple_last = NULL;

// push to stack
void stack_push(int line, int column, int type) {
    staple *staple_new;

    // 新しい領域を確保
    staple_new = (staple*)malloc(sizeof(staple));
    if (staple_new == NULL) {
        printf("stack over flow. in short of memory");
        return;
    }

    // 渡された値をスタックに詰む
    staple_new->line = line;
    staple_new->column = column;
    staple_new->type = type;

    // リストの最後に追加する
    staple_new->staple_next = NULL;
    staple_new->staple_prev = staple_last;
    staple_last = staple_new;

    if (staple_head == NULL) {
        staple_head = staple_new;
    }

}

// 引数 = 結果取得用オブジェクト
int stack_pop(staple *ret) {
    staple *temp_staple;
    if (staple_head == NULL) {
        // スタックには何も無い:括弧の対応がとれていない
        return 0; // エラー
    }

    // 一番最後にpushされた括弧の情報を返す
    ret->line = staple_last->line;
    ret->column = staple_last->column;
    ret->type = staple_last->type;

    // retのprev nextをNULLにする
    ret->staple_next = ret->staple_prev = NULL;
    temp_staple = staple_last;

    // リストから削除する
    if (staple_last->staple_prev == NULL) {
        staple_head = NULL;
    } else {
        // もっといい実装があるはず
        // 最後の要素のprev = NULL
        // 最後から1つ前の要素のnext = NULL
        staple_last->staple_prev->staple_next = NULL;
    }

    staple_last = staple_last->staple_prev;

    // stack_pop呼び出し時における最後の要素をNULLにする
    free(temp_staple);

    return 1;
}

int main(void) {
    char buffer[4096];
    int i, len, line = 1, carryover = 0;
    staple open;

    // breakまで無限ループ
    for(;;) {
        if (fgets(buffer, 4096, stdin) == NULL) {
            break;
        }
        len = strlen(buffer);
        if (len == 0) {
            continue;
        }

        for (i = 0; i < len; i++) {
            switch(buffer[i]) {
                case '(':
                    stack_push(line, carryover + i + 1, STAPLE_SMALL);
                    break;
                case '{':
                    stack_push(line, carryover + i + 1, STAPLE_MEDIUM);
                    break;
                case '[':
                    stack_push(line, carryover + i + 1, STAPLE_LARGE);
                    break;
                case ')':
                    if (stack_pop(&open) == 0 ) {
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する開き括弧がありません\n", line, carryover + i + 1);
                        return 0;
                    }
                    if (open.type != STAPLE_SMALL) { 
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する括弧と"
                                "%d行 %d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover + i + 1);
                        return 0;
                    }
                    break;
                case '}':
                    if (stack_pop(&open) == 0 ) {
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する開き括弧がありません\n", line, carryover + i + 1);
                        return 0;
                    }
                    if (open.type != STAPLE_MEDIUM) { 
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する括弧と"
                                "%d行 %d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover + i + 1);
                        return 0;
                    }
                    break;
                case ']':
                    if (stack_pop(&open) == 0 ) {
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する開き括弧がありません\n", line, carryover + i + 1);
                        return 0;
                    }
                    if (open.type != STAPLE_LARGE) { 
                        printf("括弧の対応がとれていません\n");
                        printf("%d行 %d文字に対応する括弧と"
                                "%d行 %d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover + i + 1);
                        return 0;
                    }
                    break;
             }
        }
        if (buffer[len - 1] == '\n') {
            carryover = 0;
            line++;
        } else {
            // 4096文字呼んでも改行に出会わなかった場合
            carryover += len;
        }
    }

    // 完全に括弧の対応がとれていればスタックは空になっているはず
    if (staple_head != NULL) {
        printf("括弧の対応がとれていません\n");
        printf("開き括弧の数が多過ぎます\n");
        return -1;
    }

    printf("括弧の対応は正しくとれています\n");
    return 0;
}
