#include <stdio.h>
#define STACK_MAX 10

double stack[STACK_MAX];

// スタック頂上の位置(最下部からのオフセット)
int stack_top = 0;

// push to stack
void stack_push(double val) {
    // もしスタックが満杯の場合エラー
    if (stack_top == STACK_MAX) {
        printf("err. stack is full. \n");
    } else {
        stack[stack_top] = val;
        stack_top++;
    }
}

double stack_pop(void) {
    if (stack_top == 0) {
        printf("err. stack is empty. \n");
        return 0;
    } else {
        // 一番上の値を返す
        return stack[--stack_top];
    }
}

int main() {
    stack_push(1.45);
    double test = stack_pop();
    printf("%f", test);

    stack_push(5.44);
    stack_push(2.1);
    double test2 = stack_pop();
    printf("%f", test2);
    return 0;
}
