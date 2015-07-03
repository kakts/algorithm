// ２分木へのデータ追加を行う。
// 2分木の各nodeのデータ構造は 
// nodeの値 value
// そのnodeより小さい値の子ノードへのポインタleft
// そのnode以上の値の子ノードへのポインタright

// nodeを追加する際に、根ノードから値判定をしていって再帰で子ノードをたどっていきデータを挿入する

tree_node* create_new_node(int num) {
    tree_node *tree_new;

    // 新規nodeを作成して初期化
    tree_new = (tree_node*)malloc(sizeof(tree_node));

    if (tree_new == NULL){
        exit(0);
    }
    tree_new->left == NULL;
    tree_new->right == NULL;
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

