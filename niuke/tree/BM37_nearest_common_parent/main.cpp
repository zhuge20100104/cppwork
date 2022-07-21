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
    vector<int> get_path(TreeNode* root, int target) {
        vector<int> paths;
        auto node = root;
        while(node && node->val != target) {
            paths.push_back(node->val);
            if(node->val > target) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        paths.push_back(node->val);
        return paths;
    }

public:
     /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @param p int整型 
     * @param q int整型 
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int p, int q) {
        // write code here
        auto path1 = get_path(root, p);
        auto path2 = get_path(root, q);

        int min_len = min(path1.size(), path2.size());
        // 从后往前找，找到第一个相等的，就是最近公共子祖先
        int res {0};
        for(int i=min_len-1; i>=0; --i) {
            if(path1[i] == path2[i]) {
                res = path1[i];
                break;
            }
        }
        return res;
    }
};


// 题目: https://www.nowcoder.com/practice/7298353c24cc42e3bd5f0e0bd3d1d759?tpId=295&tqId=1025038&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    /**
     * Source Tree:
     *                   7
     *               1            12
     *           0      4    11         14
     *               3     5  
     */
    TreeNode root{7};
    TreeNode node1{1};
    TreeNode node2{12};
    TreeNode node3{0};
    TreeNode node4{4};
    TreeNode node5{11};
    TreeNode node6{14};
    TreeNode node7{3};
    TreeNode node8{5}; 

    root.left = &node1;
    root.right = &node2;
    node1.left = &node3;
    node1.right = &node4;
    node2.left = &node5;
    node2.right = &node6;
    node4.left = &node7;
    node4.right = &node8;


    Solution sol;
    auto common_ancestor = sol.lowestCommonAncestor(&root, 1, 12);
    cout << common_ancestor << endl;
    
    return EXIT_SUCCESS;
}