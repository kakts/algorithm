// bm法による文字列検索プログラム
// KMP法と比べて、検索する文字列を後ろから比較していくことにより、
// 比較回数を減らす事が出来る

#include <stdio.h>
#include <stdlib.h>

#define PATTERN_LENGTH 4

unsigned char original_text[] = "On a dark desert highway,"
                                  "cool wind in my hair,";
unsigned char original_pattern[PATTERN_LENGTH + 1] = "wind";

#define _SHOW_WORKING_

unsigned char *bm_search(unsigned char *text, unsigned char *pattern) {
  // char型全体について、その文字で一致しなかった場合
  // どれだけ比較点を移動するかのテーブル
  int table[256];
  // 本文とパターンの比較点
  int text_index, pattern_index, text_len, i;

  for (i = 0; i < 256; i++) {
    // たいていの文字は、失敗した場合
    // patternの長さぶん比較点をずらせばよい
    table[i] = PATTERN_LENGTH;
  }
  for (i = 0; i < PATTERN_LENGTH - 1; i++) {
    // パターンに含まれている文字はその文字にあわせてずらす
    // パターンに同じ文字が含まれていた場合は後方の文字優先
    table[pattern[i]] = PATTERN_LENGTH - i - 1;
  }

  // 本文の長さを確認する
  for (text_len = 0; text[text_len] != '\0'; ++text_len);

  // 最初の比較点は、テキストのパターン文字目から
  text_index = PATTERN_LENGTH - 1;

  while(text_index < text_len) {
    #ifdef _SHOW_WORKING_
      // わかりやすさのため、今何を比較しているか表示
      printf("    本文:%s \nパターン:", original_text);
      for (i = 0; i < text_index - PATTERN_LENGTH + 1; i++) {
        printf(" ");
      }
      printf("%s \n", pattern);
    #endif

    // パターンの後ろから比較を始める
    pattern_index = PATTERN_LENGTH - 1;
    while(text[text_index] == pattern[pattern_index]) {
      if (pattern_index == 0) {
        // パターンの先頭文字まですべて比較成功
        return text + text_index;
      }
      text_index--;
      pattern_index--;
    }

    if (table[text[text_index]] > PATTERN_LENGTH - pattern_index) {
      // その文字に応じて、比較点を移動
      text_index += table[text[text_index]];
    } else {
      // パターンが前にずれるのを防ぐ
      // 下の式はパターンを1つ後ろにずらしている
      text_index += PATTERN_LENGTH - pattern_index;
    }
  }

  return NULL;
}

int main(void) {
  unsigned char *result;
  result = bm_search(original_text, original_pattern);
  if (result == NULL) {
    printf("見つかりませんでした \n");
  } else {
    printf("見つかりました \n");
  }

  return 0;
}
