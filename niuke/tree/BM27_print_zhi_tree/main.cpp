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
    void zhi_traversal(TreeNode* node, vector<vector<int>>& res, int level) {
        if(!node) {
            return;
        }

        if(res.size() <= level) {
            res.push_back(vector<int>());
        }

        res[level].push_back(node->val);

        if(node->left) {
            zhi_traversal(node->left, res, level+1);
        }

        if(node->right) {
            zhi_traversal(node->right, res, level+1);
        }
    }

public:
    vector<vector<int>> Print(TreeNode* pRoot) {
        vector<vector<int>> res;
        zhi_traversal(pRoot, res, 0);

        int i = 0;
        for(auto& vec: res) {
            if(i%2) {
                reverse(vec.begin(), vec.end());
            }
            ++i;
        }
        return res;
    }
};

// 题目: https://www.nowcoder.com/practice/91b69814117f4e8097390d107d2efbe0?tpId=295&tqId=23454&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    /**
     * Tree Status:
     *                  1
     *              2        3
     *                    4     5
     * */
    TreeNode root {1};
    TreeNode two {2};
    TreeNode three {3};
    TreeNode four {4};
    TreeNode five {5};

    root.left = &two;
    root.right = &three;
    three.left = &four;
    three.right = &five;

    Solution sol;
    auto res = sol.Print(&root);

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