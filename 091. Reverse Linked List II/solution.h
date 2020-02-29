#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (!(n-=m)) return head;
        ListNode preHead(0);
        preHead.next = head;
        ListNode *pre = &preHead;
        while (--m) pre = pre->next;
        ListNode *first = pre->next;
        while (n--) {
            ListNode *p = first->next;
            first->next = p->next;
            p->next = pre->next;
            pre->next = p;
        }
        return preHead.next;
    }

    ListNode *reverseBetween2(ListNode *head, int m, int n) {
        if (head == NULL || m >= n)
            return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *pBegin = &dummy, *pEnd = &dummy;

        int distance = n - m ;
        while (pEnd && distance > 0)
        {
            pEnd = pEnd->next;
            distance--;
        }
        //走m-1步
        while (pBegin && pEnd && m - 1 > 0)
        {
            pBegin = pBegin->next;
            pEnd = pEnd->next;
            m--;
        }
        if (pBegin == NULL || pEnd == NULL || pEnd->next == NULL)
        {
            return head;
        }
        
        ListNode *p = pBegin->next;
        ListNode *q = pEnd->next->next;
        
        ListNode *pre = q;
        while (p != q)
        {
            ListNode* tmp = p->next;
            p->next = pre;
            pre = p;
            p = tmp;
        }
        pBegin->next = pre;

        return dummy.next;
    }
};
