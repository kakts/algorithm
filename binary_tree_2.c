#include <stdio.h>
#include <stdlib.h>

// ２分木へのデータ追加を行う。
// 2分木の各nodeのデータ構造は 
// nodeの値 value
// そのnodeより小さい値の子ノードへのポインタleft
// そのnode以上の値の子ノードへのポインタright

// nodeを追加する際に、根ノードから値判定をしていって再帰で子ノードをたどっていきデータを挿入する

typedef struct _tag_free_node {
    // value
    int value;

    // 自分より小さい値のnode ツリー上だと自nodeの左側のnode
    struct _tag_free_node *left;

    // 自分より大きい値のnode ツリー上だと自nodeの右側のnode
    struct _tag_free_node *right;
} tree_node;

tree_node *tree_root = NULL;

tree_node* create_new_node(int num) {
    tree_node *tree_new;

    // 新規nodeを作成して初期化
    tree_new = (tree_node*)malloc(sizeof(tree_node));

    if (tree_new == NULL){
        exit(0);
    }
    tree_new->left = NULL;
    tree_new->right = NULL;
    tree_new->value = num;
    return tree_new;
}

/**
 * nodeを新規追加する
 * @param {int} num 挿入する値
 * @param {*tree_node} node 値を挿入するツリーの根をさすポインタ
 */
void insert_tree(int num, tree_node *node) {
    // 1つも挿入されていない場合
    if (node == NULL) {
        tree_root = create_new_node(num);
        return;
    }

    // numが現在のnodeの値よりも小さい場合　
    if (num < node->value) {
        // nodeのleft側にinsertするが、既に要素が詰まっていた場合
        if (node->left != NULL) {
            insert_tree(num, node->left);
        } else {
            // そのままnode->leftに追加
            node->left = create_new_node(num);
        }
    } else {
        // numが現在のnodeの値以上の場合
        if (node->right != NULL) {
            insert_tree(num, node->right);
        } else {
            node->right = create_new_node(num);
        }

    }

    return;
}

// 指定した値のnodeを探す
// 見つからなかった場合はNULL
tree_node* find_value(tree_node* node, int val) {
    if (node->value > val) {
        // treeの左側を探索
        if (node->left == NULL) {
            return NULL;
        }
        return find_value(node->left, val);
    }

    // 自分より大きい値ならば右側を探索
    if (node->value < val) {
        if (node->right == NULL) {
            return NULL;
        }
        return find_value(node->right, val);
    }

    // 見つかった場合はnodeを返す
    return node;
}


// nodeの削除
// 成功の場合は1 失敗した場合は0を返す
int delete_node(int val) {
    tree_node *node, *parent_node;
    tree_node *left_biggest;
    int direction;
    
    node = tree_root;
    parent_node = NULL;
    direction = 0;

    // 削除すべき対象をみつける
    while (node != NULL && node->value != val) {
        if (node->value > val) {
            // 親nodeを自nodeにする
            parent_node = node;

            // 左側を探索する
            node = node->left;

            // 親ノードのどちらを探索するかを指定する
            // -1 = 親の左側
            direction = -1;
        } else {
            parent_node = node;
            node = node->right;
            direction = 1;
        }
    }
    if (node == NULL) {
        return 0;
    }

    // 子node　左か右どちらかがNULLの場合
    if (node->left == NULL || node->right == NULL) {
        
        if (node->left == NULL) {
            // 親のポインタ変更
            if (direction == -1) {
                // ?
                parent_node->left = node->right;
            } else if (direction == 1) {
                parent_node->right = node->right;
            } else if (direction == 0) {
                tree_root = node->right;
            }
        } else {
            // 親のポインタ変更
            if (direction == -1) {
                parent_node->left = node->left;
            } else if (direction == 1) {
                parent_node->right = node->left;
            } else if (direction == 0) {
                tree_root = node->left;
            }
        }

        free(node);
    } else {
        // 子nodeどちらもNULLで無い場合

        // 1:nodeの左側の最も大きな値を取得する
        // 2:取得した値を、削除対象のnodeのvalに設定し、
        // 3:その後に、1で取得したnodeを解放する
        
        // left_biggest, parent_node, direction初期化
        // whileループでleft_biggestを取得
        left_biggest = node->left;
        parent_node = node;
        direction = -1;
        while(left_biggest->right != NULL) {
            parent_node = left_biggest;
            left_biggest = left_biggest->right;
            direction = 1;
        }

        // 取得したleft_biggestの値をnodeに代入
        node->value = left_biggest->value;
        if (direction == -1) {
            parent_node->left = left_biggest->left;
        } else {
            parent_node->right = left_biggest->left;
        }
        free(left_biggest);
    }

    return 1;
}

// treeの状態を表示させる
void print_tree(int depth, tree_node* node) {
    int i;

    if (node == NULL) {
        return;
    }

    print_tree(depth + 1, node->left);
    for (i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%d\n", node->value);
    print_tree(depth + 1, node->right);
}

// 指定したnodeのメモリ解放
// 子nodeもあわせて解放
void free_tree(tree_node* node) {
    if (node == NULL)  {
        return;
    }

    // 子nodeのメモリ解放が先
    free_tree(node->left);
    free_tree(node->right);

    // 自分自身を解放
    free_tree(node);
}

int main(void) {
    int i, action;

    for (i = 0; i < 10; i++) {
        // ツリーにランダムな値で10個node追加
        insert_tree(rand() % 99 + 1, tree_root);
    }

    for (;;) {
        print_tree(0, tree_root);
        printf("実行する操作のタイプを入力 \n \t 1:追加\t 2: 検索 \t 3:削除 \t それ以外: 終了");
        scanf("%d", &action);
        switch(action) {
            case 1:
                printf("1〜100の範囲で追加する数字を入力してください");
                scanf("%d", &i);
                if (i < 1 || i > 100) {
                    continue;
                }
                insert_tree(i, tree_root);
                break;
             case 2:
                printf("検索する数字を入力 \n");
                scanf("%d", &i);
                if (find_value(tree_root, i) != NULL) {
                    printf("%dを発見しました\n", i);
                } else {
                    printf("%dは見つかりませんでした\n", i);
                }
                break;
             case 3:
                printf("削除する数字を入力してください\n");
                scanf("%d", &i);
                if (delete_node(i) == 1) {
                    printf("%dを削除しました\n", i);
                } else {
                    printf("%dは見つかりませんでした\n", i);
                }
                break;
             default:
                free_tree(tree_root);
                return 0;
         }
    }
}



