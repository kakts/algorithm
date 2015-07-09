// 7パズルを解く
// ①ターンで可能なパターンをキューに詰めていって、
// それらをさらに１手ずつ可能なパターンを列挙させキューにつめ、
// 完成するか判定させる
#include <stdio.h>
#include <stdlib.h>

// 今までに現れた局面を記録する配列
// この配列は、キュー代わりにも使われる
typedef struct tagPATTERN {
  unsigned long hash;
  int pattern_from;
} PATTERN;
PATTERN *history;

int history_count = 0; // 現在のパターンの個数
int queue_bottom; // キューの末尾位置を表す添字

// 局面と対応する数字を作り出す関数
unsigned long make_hash(char* pattern) {
  unsigned long hash;
  int i;

  hash = 0;
  for (i = 0; i < 8; i++) {
    hash |= ((unsigned long)(pattern[7 - i])) << (i * 4);
  }
  return hash;
}

// 数字から局面を復元する関数
void pattern_from_hash(char* pattern, unsigned long hash) {
  int i;
  for (i = 0; i < 8; i++) {
    pattern[7 - i] = (char)((hash >> (i * 4)) & 0xf);
  }
}

void save_history(char* pattern, int pattern_from) {
  int i;
  unsigned long hash;

  hash = make_hash(pattern);
  // 今までの局面と比較
  for (i = 0; i < history_count; i++) {
    if (history[i].hash == hash) {
      return;
    }
  }

  history_count++;
  history = (PATTERN*) realloc(history, sizeof(PATTERN) * (history_count));
  if (history == NULL) {
    printf("メモリが足りません");
    exit(0);
  }

  history[history_count - 1].hash = hash;
  history[history_count - 1].pattern_from = pattern_from;
}

int solve_puzzle(void) {
  int blank_pos;
  unsigned long hash;
  char pattern[8];

  queue_bottom = 0;
  while(queue_bottom != history_count) {
    // キューが空になるまで繰り返す

    // キューから1つ取得
    hash = history[queue_bottom].hash;

    if (hash == 0x12345670) {
      // 解にたどりついたら終了
      return 1;
    }

    pattern_from_hash(pattern, hash);
    for (blank_pos = 0; blank_pos < 8; blank_pos++) {
      if (pattern[blank_pos] == 0) {
        break;
      }
    }
    if (blank_pos > 3) {
      // 上からあいている場所へ移動
      pattern[blank_pos] = pattern[blank_pos - 4];
      pattern[blank_pos - 4] = 0;

      // 新しいパネル配置を保存した後、元の位置に戻す
      save_history(pattern, queue_bottom);
      pattern_from_hash(pattern, hash);
    }
    if (blank_pos < 4) {
      // 下からあいている場所へ移動
      pattern[blank_pos] = pattern[blank_pos + 4];
      pattern[blank_pos + 4] = 0;

      save_history(pattern, queue_bottom);
      pattern_from_hash(pattern, hash);
    }
    if (blank_pos != 0 && blank_pos != 4) {
      // 上からあいている場所へ移動
      pattern[blank_pos] = pattern[blank_pos - 1];
      pattern[blank_pos - 1] = 0;

      save_history(pattern, queue_bottom);
      pattern_from_hash(pattern, hash);
    }
    if (blank_pos != 3 && blank_pos != 7) {
      // 上からあいている場所へ移動
      pattern[blank_pos] = pattern[blank_pos + 1];
      pattern[blank_pos + 1] = 0;

      save_history(pattern, queue_bottom);
      pattern_from_hash(pattern, hash);
    }
    queue_bottom++;
  }
  return 0;
}

int main(void) {
  int last, i;
  char pattern[8] = {2, 7, 1, 4, 5, 0, 3, 6};

  history = NULL;
  // 最初の1つ目のパターン記録
  save_history(pattern, -1);
  if (solve_puzzle() == 0) {
    printf("全パターン試したが見つからない\n");
  } else {
    // 解を表示
    last = -1;
    while(last != queue_bottom) {
      for (i = queue_bottom; history[i].pattern_from != last;) {
        i = history[i].pattern_from;
      }
      last = i;

      pattern_from_hash(pattern, history[last].hash);
      for (i = 0; i < 8; i++) {
        printf("%c ", pattern[i]? pattern[i] + '0': ' ');
        if (i % 4 == 3) {
          printf("\n");
        }
      }
      getchar();
    }
  }

  free(history);
  return 0;
}
