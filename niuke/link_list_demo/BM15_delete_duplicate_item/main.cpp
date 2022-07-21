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
    ListNode *next;
};


class Solution {
public:

    /**
     * 方法2： 单个指针 O(n)
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* deleteDuplicates2(ListNode* head) {
        auto* p = head;

        if(p == nullptr) {
            return head;
        }

        while(p->next != nullptr) {
            if(p->val == p->next->val) {
                p->next = p->next->next;
            } else {
                p = p->next;
            }
        }

        return head;
    }
    
    /**
     * 方法1： 暴力法: O(n^2)
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* deleteDuplicates(ListNode* head) {
        // write code here

        if(head == nullptr) {
            return head;
        }

        for(auto i = head; i!=nullptr; i=i->next) {
            for(auto j = i->next; j!=nullptr; j=j->next) {
                if(i->val == j->val) {
                    i->next = j->next;
                }
            }
        }
        return head;
    }
};

// 题目: https://www.nowcoder.com/practice/c087914fae584da886a0091e877f2c79?tpId=295&tqId=664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    ListNode l3 = {1, nullptr};
    ListNode l2 = {1, &l3};
    ListNode l1 = {1, &l2};

    Solution sol;
    auto res = sol.deleteDuplicates(&l1);
    auto p = &l1;
    while(p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }

    cout << endl;

    return EXIT_SUCCESS;
}