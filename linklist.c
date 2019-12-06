
//插表头法
void reverseLinklist(Node* pHead)
{
    Node* curr = pHead;
    Node* prev = NULL;
    while (curr != NULL)
    {
        Node* tmp = curr->next;
        // Insert to head
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    return prev;
}

Node *reverseRecursive(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node* p =reverseRecursive(head->next);
    head->next->next = head; //让下一个节点指向自己
    head->next = NULL; //断开自己原来的下一个节点指向
    return p;
}

/*
 *设置两个指针(fast, slow)，初始值都指向头，slow每次前进一步，fast每次前进二步，如果链表存在环，则fast必定先进入环，而slow后进入环，两个指针必定相遇
 *
 */
int hasCircle(Node *head)
{
     Node *slow=head;
     Node *fast=head;
     while( fast && fast->next)
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

