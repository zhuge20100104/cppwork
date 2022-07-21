#include "printer/printer.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode(int val_): val{val_} {}
};

class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @return bool布尔型
     */
    bool isCompleteTree(TreeNode* root) {
        // write code here
        // 空树 是一颗完全二叉树
        if(!root) {
            return true;
        }

        queue<TreeNode*> q;

        q.push(root);

        bool is_completed {true};
        while(!q.empty()) {
            auto node = q.front();
            q.pop();

            if(!node) {
                is_completed = false;
                continue;
            }
            // 如果出现了叶子节点，还要再次遍历，说明不是完全二叉树
            if(!is_completed) {
                return false;
            }

            q.push(node->left);
            q.push(node->right);
        }

        return true;
    }
};

// 题目: https://www.nowcoder.com/practice/7298353c24cc42e3bd5f0e0bd3d1d759?tpId=295&tqId=1025038&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    /**
     * Source Tree:
     *          2
     *      1      3
     */
    TreeNode root{2};
    TreeNode node1{1};
    TreeNode node2{3};

    root.left = &node1;
    root.right = &node2;

    Solution sol;
    auto res = sol.isValidBST(&root);
    cout << std::boolalpha << res << endl;

    return EXIT_SUCCESS;
}