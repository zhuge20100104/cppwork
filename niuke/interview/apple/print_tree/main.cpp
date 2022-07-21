#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

template <typename T>
struct TreeNode {
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

class Solution {
public:
    // 先根遍历
    template <typename T>
    void print_tree(TreeNode<T> const* head) {
        if(!head) return;
        cout << head->val << " ";
        print_tree(head->left);
        print_tree(head->right);
    }
};

int main(int argc, char* argv[]) {
    /**
     * Tree:
     *       1
     *    2     3
     *  4   5
     **/

    TreeNode<int> root {1};
    TreeNode<int> left1_1 {2};
    TreeNode<int> right1_1 {3};

    TreeNode<int> left2_1 {4};
    TreeNode<int> right2_1 {5};

    root.left = &left1_1;
    root.right = &right1_1;

    left1_1.left = &left2_1;
    left1_1.right = &right2_1;

    Solution sol;
    sol.print_tree(&root);

    return EXIT_SUCCESS;
}