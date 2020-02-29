/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
}; 
 
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head && head->next)
            for (ListNode *slower = head, *faster = head->next; faster && faster->next; slower = slower->next, faster = faster->next->next)
                if (slower == faster) return true;
        return false;
    }

    bool hasCycle2(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            if (slow == fast) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }
};
