#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.
Example:
Given a binary tree
          1
         / \
        2   3
       / \     
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
*/
int depth(TreeNode* root, int& ret) {
    if (!root) return 0;
    int leftDepth = depth(root->left, ret);
    int rightDepth = depth(root->right, ret);
    ret = std::max(ret, leftDepth + rightDepth);
    return std::max(leftDepth, rightDepth) + 1;
}
//最大路径一定存在于某棵子树，且最大长度为其左子树深度+右子树深度
int diameterOfBinaryTree(TreeNode* root) {
    int ret = 0;
    depth(root, ret);
    return ret;
}

/********************************************************************************** 
 * 
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the 
 * tree.
 * 
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is 
 * defined between two nodes v and w as the lowest node in T that has both v and w as 
 * descendants (where we allow a node to be a descendant of itself).”
 * 
 *         _______3______
 *        /              \
 *     ___5__          ___1__
 *    /      \        /      \
 *    6      _2       0       8
 *          /  \
 *          7   4
 * 
 * For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example 
 * is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according 
 * to the LCA definition.
 **********************************************************************************/
//递归法（的问题一般都可以转换为递归因为树本来就是递归描述），
//弊端就是：如需N次查询，则总体复杂度会扩大N倍，故这种暴力解法仅适合一次查询，不适合多次批量查询。
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    //return if found or not found, return NULL if not found
    if (!root || root==p || root==q) return root;

    //find the LCA in left tree
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    //find the LCA in right tree
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    //left==NULL means both `p` and `q` are not found in left tree.
    if (!left) return right;
    //right==NULL means both `p` and `q` are not found in right tree.
    if (!right) return left;

    // left!=NULL && right !=NULL, which means `p` & `q` are seperated in left and right tree.
    return root;
}

TreeNode* lowestCommonAncestorOfBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val > root->val && q->val > root->val) {
            //如果p、q都大于root，则在其右子树中查找
            root = root->right;
        } else if (p->val < root->val && q->val < root->val) {
            //如果p、q都小于root，则在其左子树中查找
            root = root->left;
        } else {
            //否则p、q分别位于左右子树中，返回root即可。
            return root;
        }
    }

    return NULL;
}

//
// if a node has 0 coin, which means one move from its parent.
//               1 coin, which means zero move from its parent.
//               N coins, which means N-1 moves to its parent.
//
// So, we can simply know, the movement = coins -1.
// - negative number means the the coins needs be moved in.
// - positive number means the the coins nees be moved out.
//
// A node needs to consider the movement requests from both its left side and right side.
// and need to calculate the coins after left and right movement.
//
// So, the node coins  = my conins - the coins move out + the coins move in.
//
// Then we can have to code as below.
//
int dfs(TreeNode* root, int& result) {
    if (root == NULL) return 0;

    int left_move = dfs(root->left, result);
    int right_move = dfs(root->right, result);
    //result是移动步数，所以要取绝对值
    result += (abs(left_move) + abs(right_move));

    // the coin after movement: coins = root->val +left_move + right_move
    // the movement needs:  movement = coins - 1
    //coins-1是本题的核心
    return root->val + left_move + right_move - 1;
}
//问题描述：https://leetcode-cn.com/problems/distribute-coins-in-binary-tree/
//大致意思是N个节点的二叉树，每个节点上有若干个金币（也可能0个），总共有N个金币，问一共要经过多少次移动使得每个节点上只有1个金币
int distributeCoins(TreeNode* root) {
    int result = 0;
    dfs(root, result);
    return result;
}

TreeNode* sortedArrayToBST(vector<int>& arr) {
    return createBST(arr, 0, arr.size()-1);
}
TreeNode* createBST(vector<int>& arr, int low, int high) {
    if (low > high) return NULL;
    int mid = (low + high) >> 1;
    TreeNode* node = new TreeNode(arr[mid]);
    node->left = createBST(arr, low, mid - 1);
    node->right = createBST(arr, mid + 1, high);
    return node;
}

TreeNode* sortedListToBST(ListNode* head) {
    int len = 0;
    for (ListNode* p = head; p; p=p->next) len++;
    return createBST2(head, 0, len-1);
}
TreeNode* createBST2(ListNode*& head, int low, int high) {
    if (low > high || !head) return NULL;
    int mid = (low + high) >> 1;
    TreeNode* left = createBST2(head, low, mid-1);
    TreeNode* node = new TreeNode(head->val);
    node->left = left;

    head = head->next;

    node->right = createBST2(head, mid+1, high);
    return node;
}
