#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next{nullptr};
    ListNode(int val_): val{val_} {}
    ListNode(int val_, ListNode* next_): val{val_}, next{next_} {}
};


class Solution {

public:
    /**
     * 
     * @param head ListNode类 
     * @param k int整型 
     * @return ListNode类
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        // write code here
        
    }
};

// 题目: https://www.nowcoder.com/practice/c087914fae584da886a0091e877f2c79?tpId=295&tqId=664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    ListNode l5 = {5, nullptr};
    ListNode l4 = {4, &l5};
    ListNode l3 = {3, &l4};
    ListNode l2 = {2, &l3};
    ListNode l1 = {1, &l2};

    Solution sol;
    auto res = sol.reverseBetween(&l1, 2, 4);
    auto p = res;
    while(p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }

    cout << endl;

    return EXIT_SUCCESS;
}