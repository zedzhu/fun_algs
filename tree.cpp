#include <cstdio>
#include <algorithm>

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    //最大路径一定存在于某棵子树，且最大长度为其左子树深度+右子树深度
    int diameterOfBinaryTree(TreeNode* root) {
        int ret = 0;
        depth(root, ret);
        return ret;
    }

    int depth(TreeNode* root, int& ret) {
        if (!root) return 0;
        int leftDepth = depth(root->left, ret);
        int rightDepth = depth(root->right, ret);
        ret = std::max(ret, leftDepth + rightDepth);
        return std::max(leftDepth, rightDepth) + 1;
    }
};