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

    ListNode* ReverseList2(ListNode* pHead) {
        if(!pHead) {
            return pHead;
        }

        ListNode* tempHead{pHead};
        stack<ListNode*> st;
        while(tempHead) {
            st.push(tempHead);
            tempHead = tempHead->next;
        }

        ListNode* ret{st.top()};
        ListNode* ret_head {ret};
        st.pop();
        while(!st.empty()) {
            ListNode* temp{st.top()};
            st.pop();
            ret->next = temp;
            ret = ret->next; 
        }
        // 最后一个要补空
        ret->next = nullptr;
        return ret_head;
    }

    ListNode* ReverseList(ListNode* pHead) {

        // 1 -> 2 -> 3 -> 4 -> 5 -> nullptr
        // nullptr <- 1 <- 2  <-  3  <-  4  <-  5
        /**
         *  pre       cur
         *                 cur_next
        */
        ListNode* pre {nullptr};
        ListNode* cur {pHead};
        while(cur) {
            // 缓存cur_next，免得待会找不到
            auto cur_next = cur->next;
            // 反向连接
            cur->next = pre;
            // pre往后移一步 
            pre = cur;
            // 最后一步肯定要移动指针
            cur = cur_next;
        }

        return pre;
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
    auto res = sol.ReverseList2(&l1);
    auto p = res;
    while(p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }

    cout << endl;

    return EXIT_SUCCESS;
}