
// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a sorted linked list, delete all duplicates such that each element appear only once.
* 
* For example,
* Given 1->1->2, return 1->2.
* Given 1->1->2->3->3, return 1->2->3.
* 
*               
**********************************************************************************/

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  //Better
  ListNode *deleteDuplicates(ListNode *head) {
    for (ListNode *cur = head; cur && cur->next; )
    {
      if (cur->val == cur->next->val) 
      {
        ListNode *del = cur->next;
        cur->next = del->next;
        delete del;
      }
      else cur = cur->next;
    }    
    return head;
  }

  ListNode *deleteDuplicates2(ListNode *head) {
      for(ListNode *p=head; p && p->next; ){
          if (p->val == p->next->val){
              p->next = p->next->next;
              continue;
          }
          p=p->next;
      }
      return head;
  }
};
