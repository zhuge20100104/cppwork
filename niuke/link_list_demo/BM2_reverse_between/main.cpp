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
    void reverseLinkedList(ListNode* head) {
        ListNode* pre {nullptr};
        ListNode* cur {head};
        while(cur) {
            ListNode* cur_next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = cur_next;
        }
    }
public:
    /**
     * 
     * @param head ListNode类 
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // write code here
        ListNode* dumyNode = new ListNode(-1);
        dumyNode->next = head;
        ListNode* pre = dumyNode;
        // 1. 走m-1步，到达 left的前一个节点
        for(int i=0; i<m-1; ++i) {
            pre = pre->next;
        }

        // 2. 走n-m+1步 到达right节点
        ListNode* rightNode = pre;

        for(int i=0; i<n-m+1; ++i) {
            rightNode = rightNode->next;
        }

        // 3. 截取出一个子链表
        auto leftNode = pre->next;
        auto cur = rightNode->next;

        // 4. 切断链接
        pre->next = nullptr;
        rightNode->next = nullptr;

        // 5. 翻转局部链表
        reverseLinkedList(leftNode);
        pre->next = rightNode;
        leftNode->next  = cur;

        return dumyNode->next;
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