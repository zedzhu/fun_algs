#include <cstddef>

/********************************************************************************** 
* https://leetcode.com/problems/reorder-list 
* Given a singly linked list L: L0→L1→…→Ln-1→Ln,
* reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
* 
* You must do this in-place without altering the nodes' values.
* 
* For example,
* Given {1,2,3,4}, reorder it to {1,4,2,3}.
* 
*               
**********************************************************************************/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    ListNode* reverseList(ListNode *head) {
        ListNode *curr = head, *pre = NULL;
        while (curr) {
            ListNode* tmp = curr->next;
            curr->next = pre;
            pre = curr;
            curr = tmp;
        }
        return pre;
    }

    ListNode* mergeList(ListNode *h1, ListNode* h2) {
        ListNode *p1 = h1, *p2 = h2;
        while (p1 && p2)
        {
            ListNode *p1nxt = p1->next;
            ListNode *p2nxt = p2->next;
            p1->next = p2;
            p2->next = p1nxt;
            //链表1比链表2短
            if (!p1nxt)
            {
                p2->next = p2nxt; //恢复链表2的原来指向
                break;
            }
            p1 = p1nxt;
            p2 = p2nxt;
        }

        return h1 ? h1 : h2;
    }


public:
    //40 ms(faster than 99.75%), 12 MB(less than 88.24%)
    void reorderList(ListNode *head) {
        if (head == NULL) return;
        //先找到中间节点
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        //此时slow指向中间节点
        ListNode *newHead = reverseList(slow->next);
        slow->next = NULL;
        head = mergeList(head, newHead);
    }
};
