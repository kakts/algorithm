// ハッシュマップ実装
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 英単語と和訳を保持する構造体
typedef struct {
  char *english;
  char *japanese;
} WORDSET;

// ハッシュテーブル
typedef struct {
  WORDSET **data;
  unsigned int size;
} HASHTABLE;

// 文字列のASCIIコードに重率をかけてハッシュ値を作成
unsigned int MakeHash2(char* str, unsigned int hashmax) {
  unsigned int n, length, hash, weight;

  // 文字列長
  length = strlen(str);
  for (n = weight = hash = 0; n < length; n++, weight++) {
    // 重率が256ˆ7まで到達したら、一巡して再び元に戻す
    // unsigned int の最大値の関係
    if (weight > 7) {
      weight = 0;
    }

    // 文字列のASCIIコードに、各文字の桁数分の重みをかける
    // << (4*weight)は 256ˆweightと同意
    hash += (int)str[n] << (4 * weight);
  }

  // 求めたhashに、ハッシュテーブルのサイズの剰余をとる
  return hash % hashmax;
}

// firsthashの位置が埋まっていた場合に再ハッシュを行うための関数
unsigned int ReHash(HASHTABLE *hashtable, unsigned int firsthash) {
  unsigned int hashval, k;

  // ハッシュ値が衝突した場合、
  // firstvalから kˆ2だけ後ろにあるあき位置を探す
  // k > ハッシュサイズの半分　となったらそれ以降の探索は無駄
  for (k = 1; k <= hashtable->size / 2; k++) {
    hashval = (firsthash + k * k) % hashtable->size;
    if (hashtable->data[hashval] == NULL) {
      return hashval;
    }
  }

  // あきが見つからなかったら-1返す
  return -1;
}

// newdataをhashtableに追加
void AddDataToMap(HASHTABLE *hashtable, WORDSET *newdata) {
  unsigned int hashval;
  // ハッシュ作成
  hashval = MakeHash2(newdata->english, hashtable->size);

  // もしhashの位置がすでに埋まってたらReHash
  if (hashtable->data[hashval] != NULL) {
    hashval = ReHash(hashtable, hashval);

    // あき位置が見つからなかった (mapが満杯)
    if (hashval == -1) {
      printf("%sをマップに挿入しようとしたけど空き位置なし\n", newdata->english);
      return;
    }
  }

  // hashvalの位置にnewdataへのポインタを格納
  hashtable->data[hashval] = newdata;
}

// 英単語keyに対応する和訳をhashtableから探索して返す
char *GetDataFromMap(HASHTABLE *hashtable, char *key) {
  unsigned int hashval, k;
  WORDSET *word;

  // 探索開始するハッシュ値を求める
  hashval = MakeHash2(key, hashtable->size);

  // keyと同じ値を持つデータが現れるまで探索
  for (k = 0; k <= hashtable->size / 2; k++) {
    word = hashtable->data[(hashval + k * k) % hashtable->size];
    if (word != NULL) {
      if (strcmp(key, word->english) == 0) {
        return word->japanese;
      }
    }
  }

  // ハッシュテーブルのサイズの半分に相当する回数ループしても
  // 見つからない場合は街頭データがハッシュテーブルの中にない
  return NULL;
}

// keyに関するデータをhashtableから取り除く
// データそのものは削除しない
WORDSET *DeleteDataFromMap(HASHTABLE *hashtable, char *key) {
  unsigned int hashval, k;
  WORDSET *word;

  // 探索開始するハッシュ値を求める
  hashval = MakeHash2(key, hashtable->size);

  // keyと同じ値をもつデータが現れるまで探索
  for (k = 0; k <= hashtable->size / 2; k++) {
    word = hashtable->data[(hashval + k * k) % hashtable->size];
    if (word != NULL) {
      if (strcmp(key, word->english) == 0) {
        hashtable->data[(hashval + k * k) % hashtable->size] = NULL;

        // hashtableから取り除いたデータを返す
        return word;
      }
    }
  }

  // 見つからない場合はNULL
  return NULL;
}

// hashtableを指定したサイズに初期化する
void InitHashTable(HASHTABLE *hashtable, unsigned int size) {
  hashtable->data = (WORDSET**)malloc(sizeof(WORDSET*) * size);

  // hashtableをNULLで埋める
  memset(hashtable->data, (int) NULL, sizeof(WORDSET*) * size);
  hashtable->size = size;
}

// hashtableのクリーンアップ
void CleanupHashTable(HASHTABLE *hashtable) {
  free(hashtable->data);
  hashtable->size = 0;
}

// hashtableの全データ表示
void PrintAllData(HASHTABLE *hashtable) {
  unsigned int n;
  for (n = 0; n < hashtable->size; n++) {
    if (hashtable->data[n] != NULL) {
      printf("%d:\t%s\t%s\n", n, hashtable->data[n]->english, hashtable->data[n]->japanese);
    }
  }
}

int main(void) {
  unsigned int n;
  char key[64], *japanese;
  HASHTABLE hashtable;
  WORDSET *wordfound;
  WORDSET words[5] = {
    {"dolphin", "イルカ"},
    {"beluga", "シロイルカ"},
    {"grampus", "シャチ"},
    {"medusa", "海月"},
    {"otter", "カワウソ"}
  };

  // hashtable初期化
  // サイズは素数にする
  InitHashTable(&hashtable, 503);

  // データ追加
  for (n = 0; n < 5; n++) {
    AddDataToMap(&hashtable, &words[n]);
  }

  do {
    printf("どの操作を行いますか? 1: 検索\t 2: 削除\t 3: 全表示\t 0:終了 \n");
    scanf("%d", &n);
    switch(n) {
      case 1:
        printf("検索する英単語入力: ");
        scanf("%s", key);

        japanese = GetDataFromMap(&hashtable, key);
        if (japanese != NULL) {
          printf("%sの和訳は%sです。\n", key, japanese);
        } else {
          printf("%sが見つかりませんでした\n", key);
        }
        break;
      case 2:
        printf("削除する英単語を入力してください。:");
        scanf("%s", key);
        wordfound = DeleteDataFromMap(&hashtable, key);
        if (wordfound != NULL) {
          printf("%sをマップから削除しました。\n", key);
        } else {
          printf("%sは見つかりませんでした \n", key);
        }
        break;
      case 3:
        PrintAllData(&hashtable);
        break;
    }

  } while(n != 0);
  CleanupHashTable(&hashtable);

  return 0;
}
