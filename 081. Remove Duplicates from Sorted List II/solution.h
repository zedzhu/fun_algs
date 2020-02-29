
// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// Author : Hao Chen
// Date   : 2014-06-25

/********************************************************************************** 
* 
* Given a sorted linked list, delete all nodes that have duplicate numbers, 
* leaving only distinct numbers from the original list.
* 
* For example,
* Given 1->2->3->3->4->4->5, return 1->2->5.
* Given 1->1->1->2->3, return 2->3.
* 
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
    //Better
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == NULL) return head;
        ListNode preHead(0);
        preHead.next = head;
        ListNode *pre = &preHead;
        bool isDuplicate = false;
        ListNode *p = head;
        while (p && p->next) {
            if (p->val == p->next->val) {
                ListNode *del = p->next;
                p->next = del->next;
                delete del;
                isDuplicate = true;
            } else if (isDuplicate) {
                ListNode *del = p;
                p = p->next;
                pre->next = p; //让前一个节点指向p
                delete del;
                isDuplicate = false;
            } else {
                pre = p;
                p = p->next;
            }
        }
        if (isDuplicate) {
            ListNode *del = p;
            pre->next = p->next;
            delete del;
        }
        return preHead.next;
    }

    ListNode *deleteDuplicates2(ListNode *head) {
        ListNode fake(-1);
        fake.next = head;
        head = &fake;

        ListNode *tail=head;

        bool dup = false;
        for(ListNode *p=head->next;  p && p->next; p=p->next){
            if (dup==false && p->val == p->next->val){
                dup = true;            
                continue;
            }
            if (dup==true && p->val != p->next->val){
                dup = false;
                tail->next = p->next;
                continue;
            }
            if (dup==false){
                tail = p;
            }
        }
        if (dup==true){
            tail->next = NULL;
        }
        return head->next;
    }

};
