#include "printer/printer.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode(int val_): val{val_} {}
};

class Solution {
    unordered_map<TreeNode*, int> hs;
    int depth(TreeNode* root) {
        if(!root) return 0;
        if(hs.find(root) != hs.end()) return hs[root];

        auto left = depth(root->left);
        auto right = depth(root->right);

        hs[root] = max(left, right) + 1;
        return hs[root];
    }

    bool judge(TreeNode* root) {
        if(!root) {
            return true;
        }

        return abs(hs[root->left] - hs[root->right]) <= 1 && judge(root->left) && judge(root->right); 
    }

public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        depth(pRoot);
        return judge(pRoot);
    }
};

/**
 * A special tree:
 *                  1
 *              2        3
 *          4                 5
 *       6   
 */ 
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
    auto is_balanced = sol.IsBalanced_Solution(&root);
    cout << std::boolalpha << is_balanced << endl;
    
    return EXIT_SUCCESS;
}