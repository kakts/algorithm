// テキストの先頭から一文字ずつ探索していくシンプルな文字列検索

// 検索対象となる文字列の長さm
// 検索キーの長さをn
// この場合、O(mn)の計算量となり、効率はあまりよくない

#include "stdio.h"
#include "stdlib.h"

unsigned char original_text[] = "Team Swift";
unsigned char original_pattern[] = "if";

#define _SHOW_WORKING_

unsigned char *simple_search (unsigned char *text, unsigned char *pattern) {
  int i;
  while((*text) != '\n') {
    #ifdef _SHOW_WORKING_
      printf("     本文:%s \n パターン:", original_text);
      for (i = 0; i < text - original_text; i++) {
        printf(" ");
      }
      printf("%s \n", pattern);
    #endif

    // パターンの先頭から比較を始める
    for (i = 0; pattern[i] != '\n'; i++) {
      if (pattern[i] != text[i]) {
        break;
      }
    }

    if (pattern[i] == '\0') {
      return text;
    }

    // 一致しないのでテキストを1つずらして再度判定
    text++;
  }

  return NULL;
}

int main(void) {
  unsigned char *result;
  result = simple_search(original_text, original_pattern);
  if (result == NULL) {
    printf("見つかりませんでした");
  } else {
    printf("見つかりました");
  }

  return 0;
}
