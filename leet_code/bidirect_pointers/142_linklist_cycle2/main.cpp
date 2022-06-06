#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode *head) {
        ListNode* slow = head, *fast = head;
        // 第一次相遇，应该在环的尾部
        do {
            if(!fast || !fast->next) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
        } while(fast != slow);
        
        fast = head;
        // 第二次相遇，在环的开始位置
        while(fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    ListNode head {3};
    ListNode two {2};
    ListNode zero {0};
    ListNode four {4};
    head.next = &two;
    two.next = &zero;
    zero.next = &four;
    four.next = &two;

    auto result = s.detectCycle(&head);
    if(result) {
        cout << "list has a cycle with start node: " << result->val << "\n";
    } else {
        cout << "list has no cycle\n";
    }
    return EXIT_SUCCESS;
}