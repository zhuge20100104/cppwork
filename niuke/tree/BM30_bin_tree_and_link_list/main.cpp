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
    vector<TreeNode*> node_vec;

    // 中根遍历， inorderTraversal
    void inorder_traversal(TreeNode* node) {
        if(!node) return;
        inorder_traversal(node->left);
        node_vec.push_back(node);
        inorder_traversal(node->right);
    }
public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(!pRootOfTree) return pRootOfTree;

        inorder_traversal(pRootOfTree);
        for(int i=0; i<node_vec.size() - 1; ++i) {
            node_vec[i]->right = node_vec[i+1];
            node_vec[i+1]->left = node_vec[i];
        }
        return node_vec[0];
    }
};

// 题目: https://www.nowcoder.com/practice/91b69814117f4e8097390d107d2efbe0?tpId=295&tqId=23454&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    /**
     * Tree Status:
     *             10
     *          6        14
     *       4     8  12     16  
     * */
    TreeNode root {10};
    TreeNode six {6};
    TreeNode four {4};
    TreeNode eight {8};
    TreeNode twelve {12};
    TreeNode fourteen {14};
    TreeNode sixteen {16};

    root.left = &six;
    root.right = &fourteen;
    six.left = &four;
    six.right = &eight;
    fourteen.left = &twelve;
    fourteen.right = &sixteen;

    Solution sol;
    auto head = sol.Convert(&root);
    TreeNode* temp = head;  

    stringstream ss;

    while(temp) {
        ss << temp->val << ",";
        temp = temp->right;
    }
    string res_str = ss.str();
    res_str = res_str.substr(0, res_str.size() - 1);
    cout << res_str << endl;
    return EXIT_SUCCESS;
}