#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//插表头法
ListNode* reverseLinklist(ListNode* pHead) {
    ListNode* curr = pHead;
    ListNode* prev = NULL;
    while (curr) {
        ListNode* tmp = curr->next;
        curr->next = prev; //Insert to head
        prev = curr;
        curr = tmp;
    }

    return prev;
}

ListNode *reverseRecursive(ListNode *head) {
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
bool hasCircle(ListNode *head)
{
     ListNode *slow=head;
     ListNode *fast=head;
     while (fast && fast->next) {
         slow = slow->next;
         fast = fast->next->next;
         if (!fast)   //fast reaches end 
            return false;
         if (slow == fast)
              return true;
     }

     return false;
}

/**
 * 如果一个单链表存在环，找到环的入口，返回入口指针；否则如果不存在环，返回NULL。
 * 分析过程：
 * 设slow走了x步，则fast走了2x步，相差：2x-x=x步，也即环的长度（因为fast必然要再次经过入口才能追上slow）；
 * 再设从头到入口距离为m，则slow从环入口到和fast相交的地方走了x-m步，
 * 环长度为x，则slow还需要x-(x-m)=m步才能走完一整圈重新到达入口；
 * 所以注意到两个都是m，所以让head和slow再同步走，相遇了也即走了m步了，也同时到达了环的入口。
 **/
ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (!fast) return NULL;
        if (slow == fast) { //存在环
            while (head != slow) { //head和slow会同时再次到达入口。
                head = head->next;
                slow = slow->next;
            }
            return slow;
        }
    }

    return NULL;
}

//两个链表的第一个公共结点
//p1与p2同时前进，p1到了末尾就指向head2，p2到了末尾就指向head1，避免了先计算链表长度。
//Runtime: 48 ms, faster than 83.81% of C++, Memory Usage: 14.7 MB, less than 100.00% of C++
ListNode* getIntersectionNode(ListNode *head1, ListNode *head2) {
    if (!head1 || !head2) return NULL;
    ListNode* p1 = head1;
    ListNode* p2 = head2;
    while (p1 != p2) {
        p1 = p1 ? p1->next : head2;
        p2 = p2 ? p2->next : head1;
        //下面的代码Wrong:因为如果没有相交点，会死循环，因为p1=NULL && p2=NULL无法执行p1!=p2的终止条件判断
        //p1 = p1->next; if (!p1) p1 = head2;
        //p2 = p2->next; if (!p2) p2 = head2;
    }
    return p1;
}