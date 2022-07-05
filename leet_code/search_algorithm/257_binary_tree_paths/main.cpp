#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>


using namespace std;
struct TreeNode {
    int val{0};
    TreeNode* left{nullptr}, *right{nullptr};
    TreeNode() {}
    TreeNode(int val_): val(val_)  {}
    TreeNode(int val_, TreeNode* left_, TreeNode* right_): val(val_), left(left_), right(right_) {}
};

class Solution {
    void construct_paths(TreeNode* root, string path, vector<string>& paths) {
        // root 为空，直接return
        if(!root) return;

        path += to_string(root->val);
        // 叶子节点，找到一条路径了
        if(!root->left && !root->right) {
            paths.push_back(path);
        } else { // 中间路径，接着往后面加
            path += "->";
            // 递归遍历子节点
            construct_paths(root->left, path, paths);
            construct_paths(root->right, path, paths);
        }

    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        string path{""};
        construct_paths(root, path, paths);
        return paths;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    TreeNode root(1);
    TreeNode t11(2);
    TreeNode t12(3);
    TreeNode t32(5);

    root.left = &t11;
    root.right = &t12;
    t11.right = &t32;

    auto res = s.binaryTreePaths(&root);
    cout << "Result paths: " << res << "\n";
    return EXIT_SUCCESS;
}