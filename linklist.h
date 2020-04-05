#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//插表头法
ListNode* reverseLinklist(ListNode* pHead)
{
    ListNode* curr = pHead;
    ListNode* prev = NULL;
    while (curr)
    {
        ListNode* tmp = curr->next;
        curr->next = prev; //Insert to head
        prev = curr;
        curr = tmp;
    }

    return prev;
}

ListNode *reverseRecursive(ListNode *head)
{
    if (!head || !head->next)
        return head;
    ListNode* p = reverseRecursive(head->next);
    head->next->next = head; //让下一个节点指向自己
    head->next = NULL; //断开自己原来的下一个节点指向
    return p;
}

/*
 *设置两个指针(fast, slow)，初始值都指向头，slow每次前进一步，fast每次前进二步，如果链表存在环，则fast必定先进入环，而slow后进入环，两个指针必定相遇
 *
 */
int hasCircle(ListNode *head)
{
     ListNode *slow=head;
     ListNode *fast=head;
     while (fast && fast->next)
     {
         slow = slow->next;
         fast = fast->next->next;
         if (!fast) //fast reaches end
             return 0;
         if (slow == fast)
              return 1;
     }
     return 0;
}

