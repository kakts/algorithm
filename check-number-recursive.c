#include <stdio.h>
#include <stdlib.h>

// 与えられた数値のなかで1が何回つかわれているかカウントする
int num_of_one(unsigned long value) {
    int ret;

    // valueが0桁 (もうこれ以上解析する桁がない)
    if (value == 0) {
        return 0;
    }

    // 一番下の位が1

    if (value % 10 == 1) {
        ret = 1;
    } else {
        ret = 0;
    }

    // 10で割って桁を1つずらし、再帰させる
    return ret + num_of_one(value / 10);
}

// 3項演算子を使った場合
int num_of_one_2(unsigned long value) {
    if (value == 0) {
        retunr 0;
    }
    return ( ((value % 10) == 1) ? 1 : 0) + num_of_one(value / 10);
}

