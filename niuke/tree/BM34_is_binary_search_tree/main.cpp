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
    vector<int> nodes;
    
    void inorder_traversal(TreeNode* root) {
        if(!root) return;
        inorder_traversal(root->left);
        nodes.push_back(root->val);
        inorder_traversal(root->right);
    }
    
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @return bool布尔型
     */
    bool isValidBST(TreeNode* root) {
        // write code here
        inorder_traversal(root);
        bool is_valid {true};
        for(int i=0; i<nodes.size()-1; ++i) {
            if(nodes[i] > nodes[i+1]) {
                is_valid = false;
                break;
            }
        }
        return is_valid;
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