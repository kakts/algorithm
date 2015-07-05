#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 解析対象の関数
// xˆ5 - 10xˆ4 + 25xˆ3 + 40xˆ2 + 200x - 500
double func(double x) {
  return x * x * x * x * x
    - 10.0 * x * x * x * x
    + 25.0 * x * x * x
    + 40.0 * x * x
    + 200.0 * x - 500.0;
}

// バイナリサーチ
double BinarySearch(void) {
  double left, mid, right, epsilon;

  // 精度を定義する
  // あまり小さすぎると浮動小数点演算の情報落ちの関係で
  // 解が求まらなくなる
  epsilon = 0.00001;

  // left と rightの間に確実に解がある　という範囲を指定する
  left = 1.0;
  right = 3.0;

  while(fabs(right - left) > epsilon && fabs(func(left)) > epsilon) {
    mid = (left + right) / 2.0;

    // func(left) と func(mid) が同符号の場合
    if (func(left) * func(mid) >= 0.0) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return left;
}

int main(void) {
  double d;
  d = BinarySearch();

  printf("方程式の解は %lf, そのときのfunc(x) は %lfです。", d, func(d));
  return 0;
}
