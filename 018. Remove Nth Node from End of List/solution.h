#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode **del = &head, *iter = head;
        for (int i=0; i<n; ++i, iter = iter->next) ;
        for (; iter != NULL; del = &((*del)->next), iter = iter->next ) ;
        *del = (*del)->next;
        return head;
    }

    ListNode *removeNthFromEnd2(ListNode *head, int n) {
        if (head == NULL || n <= 0) {
            return NULL;
        }
        ListNode **del = &head, *iter = head;
        for (int i=0; i<n; i++) {
            if (!iter) return head;
            iter = iter->next;
        }
        //for (; iter != NULL; del = &((*del)->next), iter = iter->next ) ;
        while (iter) {
            del = &((*del)->next);
            iter = iter->next;
        }
        *del = (*del)->next;
        return head;
    }

    ListNode *removeNthFromEnd3(ListNode *head, int n) {
        if (head == NULL || n <= 0) {
            return NULL;
        }
        //dummy节点主要考虑只有1个节点的情况，此时必须有一个指向其前一个节点的指针。
        ListNode dummy(0), *phead = &dummy;
        dummy.next = head;
        ListNode *p1 = phead, *p2 = phead;
        for (int i=0; i<n; i++) {
            if (p2==NULL) return head;
            p2 = p2->next;
        }
        //此时p2指向第n个节点。
        //让p2指向最后一个节点，而不是指向末尾
        while (p2->next) {
            p1 = p1->next;
            p2 = p2->next;
        }
        
        //p1指向要删节点的前一个节点，这是因为增加了dummy节点导致
        p1->next = p1->next->next;
        return dummy.next;
    }

};
