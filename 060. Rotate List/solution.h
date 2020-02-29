
// Source : https://oj.leetcode.com/problems/rotate-list/
// Author : Hao Chen
// Date   : 2014-06-20

/********************************************************************************** 
* 
* Given a list, rotate the list to the right by k places, where k is non-negative.
* 
* For example:
* Given 1->2->3->4->5->NULL and k = 2,
* return 4->5->1->2->3->NULL.
*               
**********************************************************************************/

#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == NULL || k == 0) return head;
        ListNode *slow = head, *fast = head;
        while (k--) {
            if (fast == NULL) fast = head;
            fast = fast->next;
        }
        if (fast == NULL) return head;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *new_head = slow->next;
        slow->next = NULL;
        fast->next = head;
        return new_head;
    }

    ListNode *rotateRight2(ListNode *head, int k) {
        if (!head || k<=0){
            return head;
        }
        //find the length of List，同时让p指向最后一个节点
        int len = 1;
        ListNode *p = head;
        while (p->next) {
            p = p->next;
            len++;
        }
        //connect the tail to head，此时p指向尾节点
        p->next = head;
        //find the left place (take care the case - k > len)
        k = len - k % len;
        
        //find the place
        for(int i=0; i<k; i++){
            p = p->next;
        }
        //此时p指向第k个节点的前一个节点
        
        //break the list
        head = p->next; //让头节点指向第k个节点
        p->next = NULL; //让第k-1个节点指向NULL，意为结尾。
        
        return head;
    }

};
