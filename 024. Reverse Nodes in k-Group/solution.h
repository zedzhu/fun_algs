// Source : https://oj.leetcode.com/problems/reverse-nodes-in-k-group/
// Author : Hao Chen
// Date   : 2014-07-05

/********************************************************************************** 
* 
* Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
* 
* If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
* 
* You may not alter the values in the nodes, only nodes itself may be changed.
* 
* Only constant memory is allowed.
* 
* For example,
* Given this linked list: 1->2->3->4->5
* 
* For k = 2, you should return: 2->1->4->3->5
* 
* For k = 3, you should return: 3->2->1->4->5
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
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (!head || !head->next || k<2) return head;
        ListNode pre(0);
        pre.next = head;

        for (ListNode *front = &pre, *back = &pre; true; front = head, back = head) {
            for (int count = k; count > 0; --count)
                if (!(back = back->next)) return pre.next;

            for (head = front->next; front->next != back; ) {
                ListNode *next = front->next;
                front->next = next->next;
                next->next = back->next;
                back->next = next;
            }
        }
        return pre.next;
    }

    ListNode *reverseKGroup2 (ListNode *head, int k) {
        if (k<=0) return head;
        ListNode dummy(0), *p = &dummy;
        dummy.next = head;

        while (p) {
            //p指向逆转k个节点后的第一个节点
            p->next = reverseList(p->next, k);
            //向后移动k-1步，让p指向第k个节点，也就是下一个group的前一个节点
            for (int i=0; p && i<k; i++){
                p = p->next;
            }
        }
        return dummy.next;
    }
    //ListNode *&head这里用引用仅仅是为了少一次指针拷贝，在Leetcode上submit可以略微提升4ms左右
    ListNode *reverseList (ListNode *&head, int k) {
        //移动k步先找到终止节点(第k+1个)
        ListNode* pEnd = head;
        while (pEnd && k>0) {
            pEnd = pEnd->next;
            k--;
        }
        //不足k个节点
        if (k>0) return head;

        //像单链表逆序一样，惟一不同的是首节点初始化不是NULL，而是终止节点pEnd
        //因为末尾第k个节点还要继续指向单链表的其它节点，并未终止
        ListNode *prev = pEnd, *curr = head;
        while (curr != pEnd) {
            ListNode *tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }
        return prev;
    }

};
