// KMP法(Knuth-Moriis-Pratt Method)
// による文字列検索

// simple_text_search.c の文字列検索に比べて、
// 同じ場所を重複して調べる必要がなくなるため
// O(n)となる

#include "stdio.h"
#include "stdlib.h"

#define PATTERN_LENGTH 13
unsigned char original_text[] = "a eighty-eighty-eighth key";
unsigned char original_pattern[PATTERN_LENGTH + 1] = "eighty-eighth";

unsigned char *kmp_search (unsigned char *text, unsigned char *pattern) {

  int table[PATTERN_LENGTH + 1] = {0, 0};
  int text_index = 1, pattern_index = 0;
  int i = 0, j;

  // まずkmpの検索に必要な情報を集め、テーブルとして保存
  while((pattern[text_index]) != '\0') {
    if (pattern[text_index] == pattern[pattern_index]) {
      // 一致したら再建策はpattern_index文字から始めればよい
      table[++text_index] = ++pattern_index;
    } else if (pattern_index == 0) {
      // パターン1文字目で不一致ならば、再検索は先頭から
      table[++text_index] = 0;
    } else {
      // パターン1文字目意外で不一致ならば
      // 再検索の位置はtableから参照
      pattern_index = table[pattern_index];
    }
  }

  while((*text) != '\0') {
    #ifdef _SHOW_WORKING_
      printf("     本文:%s \n パターン:", original_text);
      for (j = 0; j < text - original_text; ++j) {
        printf(" ");
      }
      printf("%s \n", pattern);
    #endif

    if ((*text) == pattern[i]) {
      // テキストとパターンが一致していたら
      // 1文字ずつ比較を続ける
      text++;
      if(pattern[++i] == '\0') {
        // すべて一致すれば正解
        return text - PATTERN_LENGTH;
      }
    } else if (i == 0) {
        // パターン最初の文字で失敗した場合は
        // 比較文字を1つ進める
        text++;
    } else {
        // 最初の文字でない場合は
        // table から比較位置を取得
        i = table[i];
    }
  }
  return NULL;
}

int main(void) {
  unsigned char *result;
  result = kmp_search(original_text, original_pattern);
  if (result == NULL) {
    printf("見つかりませんでした\n");
  } else {
    printf("見つかりました\n");
  }

  return 0;
}
