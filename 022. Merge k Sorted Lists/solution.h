#include <vector>
using std::vector;
#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head = NULL, **tail = &head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                *tail = l1;
                l1 = l1->next;
            } else {
                *tail = l2;
                l2 = l2->next;
            }
            tail = &((*tail)->next);
        }
        *tail = l1 ? l1 : l2;
        return head;
    }

    using VecNodeCIter = vector<ListNode *>::const_iterator;
    ListNode *mergeKLists(VecNodeCIter beg, VecNodeCIter end) {
        int distance = std::distance(beg, end);
        if (distance == 0) return NULL;
        else if (distance == 1) return *beg;
        else if (distance == 2) return mergeTwoLists(*beg, *std::next(beg));
        else return mergeTwoLists(
            mergeKLists(beg, beg + distance/2), 
            mergeKLists(beg + distance/2, end)
        );
    }
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        return mergeKLists(lists.cbegin(), lists.cend());
    }
};
