// Source : https://oj.leetcode.com/problems/swap-nodes-in-pairs/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a linked list, swap every two adjacent nodes and return its head.
* 
* For example,
* Given 1->2->3->4, you should return the list as 2->1->4->3.
* 
* Your algorithm should use only constant space. You may not modify the values in the list, 
* only nodes itself can be changed.
* 
*               
**********************************************************************************/

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
    ListNode(int x) : val(x),next(NULL) {}
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode *newHead = new ListNode(-1);
        newHead->next = head;
        for (ListNode *p1 = newHead, *p2 = head; p2 && p2->next; p1 = p2, p2 = p2->next)
        {
            p1->next = p2->next;
            p2->next = p1->next->next;
            p1->next->next = p2;
        }
        return newHead->next;
    }

    ListNode *swapPairs2(ListNode *head) {
        ListNode dummy(0), *phead = &dummy;
        dummy.next = head;
        //pp指向要交换的两个节点的前一个节点；
        //p1指向要交换的两个节点的第一个节点。
        ListNode* pp = phead, *p1 = head;
        while (p1 && p1->next)
        {
            ListNode* p2 = p1->next;
            //让pp指向要交换的第2个节点，串起逆转后的第1个节点；
            pp->next = p2;
            //让第1个节点(p1)指向第2个节点的后一个节点（保持链表连续），也即下一对pair的第一个节点
            p1->next = p2->next;
            //调转枪头，让第2个节点指向第1个节点，串起逆转后的第2个节点
            p2->next = p1;

            //让pp指向下一对pair的前一个节点，注意就是原来的第1个节点的位置，因为原来的第1个节点此时已经变成了第2个节点
            pp = p1;
            //让p1指向下一对pair的第一个节点也就是p3
            p1 = p1->next;
        }
        return dummy.next;
    }

    /*swap the list nodes physically*/ 
    ListNode *swapPairs2(ListNode *head) {
        ListNode *h = NULL;
        //using `*p` to traverse the linked list
        for (ListNode *p = head; p && p->next; p = p->next) {
            //`n` is `p`'s next node, and swap `p` and `n` physcially
            ListNode *n = p->next;
            p->next = n->next;
            n->next = p;
            //using `h` as `p`'s previous node
            if (h){
                h->next = n;
            }
            h=p;
            
            //determin the really 'head' pointer
            if (head == p){
                head = n;
            }
        }
        
        return head;
    }

    ListNode* swapPairs3(ListNode* head) {
         // Three pointers point current, previous and next node.
         ListNode *Curr=head, *Prev=NULL, *Next=NULL;

         while (Curr && Curr->next ) {
             Next = Curr->next;

             //swap nodes
             Curr->next = Next->next;
             Prev == NULL ? head = Prev = Next : Prev->next = Next;
             Next->next = Curr;

             //set the pointers to next place.
             Prev = Curr;
             Curr = Curr->next;
         }
         return head;
     }

};
