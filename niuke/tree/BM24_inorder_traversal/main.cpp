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
    vector<int> tree_res;


public:
    Solution() {
        tree_res.clear();
    }

    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) {
            return tree_res;
        }

        // 左--> 根 --> 右 中序遍历
        inorderTraversal(root->left);
        tree_res.push_back(root->val);
        inorderTraversal(root->right);
        return tree_res;
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    /**
     * Tree Status:
     *              1
     *           2
     *              3
     * */
    TreeNode root{1};
    TreeNode leaf1{2};
    TreeNode leaf2{3};

    root.left = &leaf1;
    leaf1.right = &leaf2;

    Solution sol;
    auto res = sol.inorderTraversal(&root);
    cout << "[ ";
    for(auto const& ele: res) {
        cout << ele << " ";
    }
    cout << " ]\n"; 
    return EXIT_SUCCESS;
}