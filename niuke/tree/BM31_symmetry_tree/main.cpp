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
    bool recursive_symmetrical(TreeNode* root1, TreeNode* root2) {
        // root1 和 root2都为空， 可以return true
        if(root1 == nullptr && root2 == nullptr)  {
            return true;
        }
        // 两个只有一个为空，不行。 
        // 或者两个都不为空， 节点值不相等，也不行
        if(root1 == nullptr || root2 == nullptr || root1->val != root2->val) {
            return false;
        }

        return recursive_symmetrical(root1->left, root2->right) && recursive_symmetrical(root1->right, root2->left);
    }
public:
    bool isSymmetrical(TreeNode* pRoot) {
        if(!pRoot) {
            return true;
        } 
        return recursive_symmetrical(pRoot, pRoot);
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    TreeNode root{1};
    TreeNode leaf1{2};
    TreeNode leaf2{2};

    root.left= &leaf1;
    root.right = &leaf2;

    Solution sol;
    auto res = sol.isSymmetrical(&root);
    cout << std::boolalpha << res << endl;
    
    return EXIT_SUCCESS;
}