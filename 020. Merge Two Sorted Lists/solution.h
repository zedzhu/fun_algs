/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <cstddef> 

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *header = NULL, **p;
        for (p = &header; l1 && l2; p = &(*p)->next)
        {
            if (l1->val <= l2->val)
            {
                *p = new ListNode(l1->val);
                l1 = l1->next;
            }
            else
            {
                *p = new ListNode(l2->val);
                l2 = l2->next;
            }
        }
        for (ListNode *leave = l1 ? l1 : l2; leave; leave = leave->next, p = &(*p)->next)
            *p = new ListNode(leave->val);
        return header;
    }

    ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2) {
        ListNode *head = NULL;
        ListNode **pTail = &head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                *pTail = l1;
                l1 = l1->next;
            } else {
                *pTail = l2;
                l2 = l2->next;
            }
            pTail = &((*pTail)->next);
        }
        *pTail = (l1 ? l1 : l2);
        return head;
    }

    /* merge the 2nd list into 1st list*/
    ListNode *mergeTwoLists3(ListNode* head1, ListNode* head2){
        ListNode *p1 = head1,  *p2=head2;
        ListNode dummy(0), *prev = &dummy;
        dummy.next = head1;
        while (p1 && p2) {
            if (p1->val < p2->val) {
                prev = p1;
                p1 = p1->next;
            } else {
                prev->next = p2; //让prev指向p2
                p2 = p2->next;   //p2后移
                prev = prev->next; //prev后移（指向p2）
                prev->next = p1; //prev指向p1即让原来的p2指向p1
            }
        }
        if (p2) {
            prev->next = p2;
        }
    
        return dummy.next;
    }



};
