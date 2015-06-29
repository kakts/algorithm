#include <stdio.h>
#include <stdlib.h>
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
    char buffer[256];
    double cal1, cal2;
    int i;

    do {
        printf("現在のスタック(%d個):", stack_top);
        for (i = 0; i < stack_top; i++) {
            printf("%0.3f ", stack[i]);
        }
        printf("\n>");
        gets(buffer);
        switch(buffer[0]) {
            case '+':
                cal1 = stack_pop();
                cal2 = stack_pop();
                stack_push(cal2 + cal1);
                break;
            case '-':
                // 4 12 - の場合、 cal1 = 12 cal2 = 4
                cal1 = stack_pop();
                cal2 = stack_pop();
                stack_push(cal2 - cal1);
                break;
            case '*':
                cal1 = stack_pop();
                cal2 = stack_pop();
                stack_push(cal2 * cal1);
                break;
            case '/':
                cal1 = stack_pop();
                if (cal1 == 0) {
                    printf("invalid number: number must not be 0");
                    return -1;
                    break;
                }
                cal2 = stack_pop();
                stack_push(cal2 / cal1);
                break;
            case '=':
                break;
            default:
                stack_push(atoi(buffer));
                break;
        }
    } while(buffer[0] != '=');

    printf("answer is %f. \n", stack_pop());
    if (stack_top != 0) {
        printf("error some numbers are remained in stack");
        return -1;
    }

    return 0;
}
