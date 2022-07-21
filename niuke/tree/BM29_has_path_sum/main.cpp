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
     * @param root TreeNode类 
     * @param sum int整型 
     * @return bool布尔型
     */
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) {
            return false;
        }

        if(!root->left && !root->right && root->val == sum) {
            return true;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
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
    auto has_sum = sol.hasPathSum(&root, 9);
    cout << std::boolalpha << has_sum << endl;

    return EXIT_SUCCESS;
}