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
#include <deque>
#include <cstring>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    TreeNode(int val_): val{val_} {}
};

class Solution {
    int const INF = std::numeric_limits<int>::max();
   
public:
    char* Serialize(TreeNode *root) {        
        if(!root) return "";
        stringstream ss;
        
        queue<TreeNode*> d;
        d.push(root);
        while(!d.empty()) {
            auto poll = d.front();
            d.pop();
            ss << poll->val << "_";
            // 说明不是空节点
            if(poll->val != INF) {
                d.push(poll->left ? poll->left: new TreeNode{INF});
                d.push(poll->right ? poll->right: new TreeNode{INF});
            }
        }
        
        string res = ss.str();
        char* ret = new char[res.size()];
        memcpy(ret, res.data(), res.size());
        return ret;
    }

    TreeNode* Deserialize(char *str) {
        string s{str};
        if(s == "") return nullptr;

        // 根据分割符进行分割
        stringstream ss{s};
        vector<string> strs;
        string temp;
        while(getline(ss, temp, '_')) {
            strs.push_back(temp);
        }

        int n = strs.size();
        TreeNode* root = new TreeNode{stoi(strs[0])};
        queue<TreeNode*> d;
        d.push(root);

        for(int i=1; i<n-1; i+=2) {
            auto poll = d.front();
            d.pop();

            int a = stoi(strs[i]), b = stoi(strs[i+1]);

            // 如果左节点对应的不是INF,构造真实节点
            if(a != INF) {
                poll->left = new TreeNode{a};
                d.push(poll->left);
            }

            if(b != INF) {
                poll->right = new TreeNode{b};
                d.push(poll->right);
            }
        }
        return root;
    }

    void inorder_traversal(TreeNode* root) {
        if(!root || root->val == INF) return;
        inorder_traversal(root->left);
        cout << root->val << " ";
        inorder_traversal(root->right);
    }
};

// 题目: https://www.nowcoder.com/practice/7298353c24cc42e3bd5f0e0bd3d1d759?tpId=295&tqId=1025038&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    /**
     * Source Tree:
     *              1
     *          2         3
     *                6      7
     */
    TreeNode root{1};
    TreeNode node1{2};
    TreeNode node2{3};
    TreeNode node3{6};
    TreeNode node4{7};

    root.left = &node1;
    root.right = &node2;
    node2.left = &node3;
    node2.right = &node4;


    Solution sol;
    auto serialized_str = sol.Serialize(&root);
    cout << serialized_str << endl;
    
    auto node = sol.Deserialize(serialized_str);

    sol.inorder_traversal(node);
    cout << endl;
    
    return EXIT_SUCCESS;
}