#include <stdio.h>

//3つ以上の数の最大公約数を求める
// 通常のgcd関数を再帰させて求める

#define MAX 6
int N[MAX] = {98, 140, 84, 28, 42, 126};



int gcd(int a, int b) {
    int i;
    for (i = a; i > 0; i--) {
        // a と bどちらもiで割り切れていたら終了
        if (a % i == 0 && b % i == 0) {
            break;
        }
    }
    return i;
}

// 
int multi_gcd(int n) {
    // n==1 数が2つしかない場合は、普通にgcdを呼ぶ
    if (n == 1) {
        return gcd(N[0], N[1]);
    }

    // n > 1の場合は、N[n] と　N[0]..N[n-1]のgcdを呼び出す
    return gcd(N[n], multi_gcd(n-1));
}

int main(void) {
    printf("配列Nの最大公約数は%dです。:", multi_gcd(MAX - 1));
    return 0;
}

