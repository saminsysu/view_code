#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define ALPHABET_SIZE 26

/*
Trie树
*/

struct trie_node {
	int count;   // 记录该节点代表的单词的个数
    trie_node *children[ALPHABET_SIZE]; // 各个子节点 
};

trie_node* create_trie_node() {
    trie_node* pNode = new trie_node();
    pNode -> count = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        pNode->children[i] = nullptr;
    return pNode;
}

void trie_insert(trie_node* root, char* key) {
    trie_node* node = root;
    char* p = key;
    while(*p) {
        if(node -> children[*p-'a'] == NULL) {
            node -> children[*p-'a'] = create_trie_node();
        }
        node = node -> children[*p-'a'];
        ++p;
    }
    node->count += 1;
}

int trie_search(trie_node* root, char* key) {
    trie_node* node = root;
    char* p = key;
    while(*p && node != NULL) {
        node = node -> children[*p-'a'];
        ++p;
    }

    if(node == NULL)
        return 0;
    else
        return node -> count;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 二叉树前序遍历

// 递归实现

void pre_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    result.push_back(roo -> val);
    if (root -> left != nullptr) {
        pre_order(root -> left, result);
    }
    if (root -> right != nullptr) {
        pre_order(root -> right, result);
    }

}

// 非递归实现

void pre_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode *> nodes;
    TreeNode *temp = root;
    while (temp != nullptr || !nodes.empty()) {
        while (temp != nullptr) {
            result.push_back(temp -> val);
            nodes.push(temp);
            temp = temp -> left;
        }
        temp = nodes.top();
        nodes.pop();
        temp = temp -> right;
    }
}

// 二叉树中序遍历

// 递归实现

void in_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    if (root -> left != nullptr) {
        in_order(root -> left, result);
    }
    result.push_back(roo -> val);
    if (root -> right != nullptr) {
        in_order(root -> right, result);
    }
}

// 非递归实现

void in_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode *> nodes;
    TreeNode *temp = root;
    while (temp != nullptr || !nodes.empty()) {
        while (temp != nullptr) {
            nodes.push(temp);
            temp = temp -> left;
        }
        temp = nodes.top();
        nodes.pop();
        result.push_back(temp -> val);
        temp = temp -> right;
    }
}


// 二叉树后序遍历

// 递归实现
void post_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    if (root -> left != nullptr) {
        post_order(root -> left, result);
    }
    if (root -> right != nullptr) {
        post_order(root -> right, result);
    }
    result.push_back(roo -> val);
}

// 非递归实现

void post_order(TreeNode * root, vector &result) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode *> nodes;
    TreeNode *temp = root, *last_visit = nullptr;
    while (temp != nullptr || !nodes.empty()) {
        while (temp != nullptr) {
            nodes.push(temp);
            temp = temp -> left;
        }
        temp = nodes.top();
        if (temp -> right == nullptr || temp -> right == last_visit) {
            result.push_back(temp -> val);
            nodes.pop();
            last_visit = temp;
            temp = nullptr;
        } else {
            temp = temp -> right;
        }
    }
}

int main()
{
    // 关键字集合
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie_node* root = create_trie_node();

    // 创建trie树
    for(int i = 0; i < 8; i++)
        trie_insert(root, keys[i]);

    // 检索字符串
    char s[][32] = {"Present in trie", "Not present in trie"};
    printf("%s --- %s\n", "the", trie_search(root, "the")>0?s[0]:s[1]);
    printf("%s --- %s\n", "these", trie_search(root, "these")>0?s[0]:s[1]);
    printf("%s --- %s\n", "their", trie_search(root, "their")>0?s[0]:s[1]);
    printf("%s --- %s\n", "thaw", trie_search(root, "thaw")>0?s[0]:s[1]);

    return 0;
}
