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
     * 
     * @param t1 TreeNode类 
     * @param t2 TreeNode类 
     * @return TreeNode类
     */
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        // write code here
        // 一种特殊情况,t1,t2都为空，也是return nullptr   
        if(!t1) {
            return t2;
        }

        if(!t2) {
            return t1;
        }

        TreeNode* head = new TreeNode(t1->val + t2->val);
        head->left = mergeTrees(t1->left, t2->left);
        head->right = mergeTrees(t1->right, t2->right);  
        return head;
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
    TreeNode root1{1};
    TreeNode leaf1{3};
    TreeNode leaf2{2};
    TreeNode leaf3{5};

    root1.left = &leaf1;
    root1.right = &leaf2;
    leaf1.left = &leaf3;


    TreeNode root2 {2};
    TreeNode leaf21 {1};
    TreeNode leaf22 {3};
    TreeNode leaf23 {4};
    TreeNode leaf24 {7};
    root2.left = &leaf21;
    root2.right = &leaf22;
    leaf21.right = &leaf23;
    leaf22.right = &leaf24;


    Solution sol;
    auto res = sol.mergeTrees(&root1, &root2);
    sol.inorder_traversal(res);
    return EXIT_SUCCESS;
}