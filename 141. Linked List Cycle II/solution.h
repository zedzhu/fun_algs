#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head && head->next)
            for (ListNode *slow = head, *fast = head->next; fast && fast->next; slow = slow->next, fast = fast->next->next)
                if (slow == fast)
                    for (slow = slow->next; true; head = head->next, slow = slow->next)
                        if (slow == head) return slow;
        return NULL;
    }

    //注意分析，设slow走了x步，则fast走了2x步，相差：2x-x=x步，也即环的长度；
    //再设从头到入口距离为m，则slow从环入口到和fast相交的地方走了x-m步，
    //环长度为x，则slow还需要x-(x-m)=m步才能走完一整圈重新到达入口；
    //所以注意到两个都是m，所以让head和slow再同步走，相遇了也即走了m步了，也同时到达了环的入口
    ListNode *detectCycle2(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (!fast) return NULL;
            if (slow == fast) {
                while (head != slow) { //head和slow会同时再次到达入口。
                    head = head->next;
                    slow = slow->next;
                }
                return slow;
            }
        }

        return NULL;
    }

};
