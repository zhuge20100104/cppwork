#include "printer/printer.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <numeric>
#include <set>

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
     * @param o1 int整型 
     * @param o2 int整型 
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        // write code here
        // key是当前值，value是parent值
        unordered_map<int, int> parent;
        queue<TreeNode*> qu;
        qu.push(root);
        parent.insert({root->val, numeric_limits<int>::min()});

        while((parent.find(o1) == parent.end()) || (parent.find(o2) == parent.end())) {
            auto node = qu.front();
            qu.pop();
            if(node->left) {
                parent.insert({node->left->val, node->val});
                qu.push(node->left);
            }

            if(node->right) {
                parent.insert({node->right->val, node->val});
                qu.push(node->right);
            }
        }

        // 弄完以后，parent里面应该就有儿子跟祖先的关系了
        set<int> ancerstors;
        while(parent.find(o1) != parent.end()) {
            ancerstors.insert(o1);
            o1 = parent[o1];
        }

        while(ancerstors.find(o2) == ancerstors.end()) {
            o2 = parent[o2];
        }

        return o2;
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