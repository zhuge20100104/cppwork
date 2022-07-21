#include "printer/printer.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode(int val_): val{val_} {}
};

class Solution {

public:
  
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pRoot TreeNode类 
     * @return TreeNode类
     */
    TreeNode* Mirror(TreeNode* pRoot) {
        // write code here
        if(!pRoot) {
            return pRoot;
        }

        auto tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;

        Mirror(pRoot->left);
        Mirror(pRoot->right);
        return pRoot;    
    }

    void inorder_traversal(TreeNode* root) {
        if(!root) return;
        inorder_traversal(root->left);
        cout << root->val << " ";
        inorder_traversal(root->right);
    }
};

// 题目: https://www.nowcoder.com/practice/7298353c24cc42e3bd5f0e0bd3d1d759?tpId=295&tqId=1025038&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    /**
     * Source Tree:
     *                8
     *           6             10
     *       5       7     9        11
     */
    TreeNode root{8};
    TreeNode node1{6};
    TreeNode node2{10};
    TreeNode node3{5};
    TreeNode node4{7};
    TreeNode node5{9};
    TreeNode node6{11};

    root.left = &node1;
    root.right = &node2;
    node1.left = &node3;
    node1.right = &node4;
    node2.left = &node5;
    node2.right = &node6;


    Solution sol;
    auto res = sol.Mirror(&root);
    sol.inorder_traversal(res);
    cout << endl;

    return EXIT_SUCCESS;
}