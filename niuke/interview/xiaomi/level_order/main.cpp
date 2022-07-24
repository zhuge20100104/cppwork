#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> levels;
        if(!root) {
            return levels;
        }

        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()) {
            vector<int> level;
            auto size = qu.size();
            for(int i=0; i<size; ++i) {
                auto node = qu.front();
                qu.pop();
                level.push_back(node->val);

                if(node->left) qu.push(node->left);
                if(node->right) qu.push(node->right);
            }

            levels.push_back(level);
        }

        reverse(levels.begin(), levels.end());
        return levels;
    }
};

int main(int argc, char* argv[]) {
    Solution sol;
    return EXIT_SUCCESS;
}