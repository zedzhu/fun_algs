#include <cstdio>
#include <algorithm>


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