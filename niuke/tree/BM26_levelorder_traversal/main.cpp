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
  

    void level_traversal(TreeNode* node, vector<vector<int>>& res, int level) {
        if(res.size()<=level) {
            res.push_back(vector<int>{});
        }
        res[level].push_back(node->val);

        if(node->left) {
            level_traversal(node->left, res, level+1);
        }

        if(node->right) {
            level_traversal(node->right, res, level+1);        
        }
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // write code here
        vector<vector<int>> res;
        level_traversal(root, res, 0);
        return res;
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    /**
     * Tree Status:
     *                  3
     *              9        20
     *                    15     7
     * */
    
    TreeNode root {3};
    TreeNode nine {9};
    TreeNode twenty {20};
    TreeNode fifteen {15};
    TreeNode seven {7};

    root.left = &nine;
    root.right = &twenty;
    twenty.left = &fifteen;
    twenty.right = &seven;

    Solution sol;
    auto res = sol.levelOrder(&root);

    stringstream ss;

    ss << "[\n";

    for(auto const& vec: res) {
        ss << " [";
        stringstream sub_ss;
        for(auto const ele: vec) {
            sub_ss << ele << ',';
        }
        string temp_arr_str = sub_ss.str();
        temp_arr_str = temp_arr_str.substr(0, temp_arr_str.size() - 1);
        ss << temp_arr_str;
        ss << "]\n";
    }
    ss << "]\n";
    cout << ss.str();
    return EXIT_SUCCESS;
}