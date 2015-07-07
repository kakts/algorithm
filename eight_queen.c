#include <stdio.h>
#include <stdlib.h>

int board[8][8]; // チェス盤の盤面

// (x, y)にクイーンがおけるかどうかチェックする関数
int check(int x, int y) {
  int p, q;
  // 左方向にすべてクイーンがあるかどうかチェック
  // (右側には絶対に存在しない)
  for (p = 0; p < x; p++) {
    if (board[p][y] == 1) {
      return 0;
    }
  }

  // 左上チェック
  p = x;
  q = y;
  while(p > 0 && q > 0) {
    if (board[--p][--q] == 1) {
      return 0;
    }
  }

  // 左下チェック
  p = x;
  q = y;
  while(p > 0 && q < 7) {
    if (board[--p][++q] == 1) {
      return 0;
    }
  }

  return 1;
}

// 現在の盤面を表示
void showboard(void) {
  int x, y;
  for (y = 0; y < 8; y++) {
    for (x = 0; x < 8; x++) {
      printf("%c ", board[x][y]? 'Q': '.');
    }
    printf("\n");
  }
}

int solve(int x) {
  int i;

  // すべての列にクイーンをおけたら
  if (x == 8) {
    return 1;
  }

  for (i = 0; i < 8; i++) {
    if (check(x, i)) {
      // (x, i)にクイーンがおけたら
      // 実際におく
      board[x][i] = 1;
      // 次の列に置く
      if (solve(x + 1)) {
        // 次の列以降が成功の場合
        // この列も成功
        return 1;
      } else {
        // 次の列以降が失敗の場合
        // クイーンを置き直す
        board[x][i] = 0;
      }
    }
  }
  return 0;
}

int main(void) {
  if (solve(0)) {
    showboard();
  }
  return 0;
}
