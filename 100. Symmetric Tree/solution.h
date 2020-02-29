#include <cstddef>
#include <stack>

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;
        TreeNode *lt = root->left, *rt = root->right;
        for (std::stack<TreeNode*> stack; !stack.empty() || (lt&&rt); ) {
            if (lt && rt) {
                if (lt->val != rt->val) return false;
                stack.push(lt->right);stack.push(rt->left);
                lt = lt->left; rt = rt->right;
            }
            else if (lt || rt) return false;
            else {
                lt = stack.top(); stack.pop();
                rt = stack.top(); stack.pop();
            }
        }
        if (lt || rt) return false;
        else return true;
    }

    bool isSymmetric2(TreeNode *root) {
        if (root == NULL) return true;
        TreeNode *lt = root->left, *rt = root->right;
        std::stack<TreeNode*> stack;
        //左右子树(lt&&rt)都存在是在迭代，往左或者往右；
        //否则栈不为空时是在回溯
        while ((lt&&rt) || !stack.empty()) {
            if (lt && rt) {
                if (lt->val != rt->val) return false;
                //左->右、右->左同时进栈
                stack.push(lt->right); stack.push(rt->left);
                //左->左、右->右同时迭代
                lt = lt->left; rt = rt->right;
            }
            else if (lt || rt) return false; //上面那个if没过，这个if就只能存在1个
            else { //两个都不存在同时stack非空
                lt = stack.top(); stack.pop();
                rt = stack.top(); stack.pop();
            }
        }
        //如果对称，到最后lt和rt肯定都为NULL
        if (lt || rt) return false;
        else return true;
    }

    bool isSymmetricRecursively(TreeNode *root) {
        if (!root) return true;
        return isSymmetric(root->left, root->right);
    }
    bool isSymmetric(TreeNode *left, TreeNode* right) {
        if (!left && !right) return true;
        if (!left || !right) return false;
        return left->val == right->val &&
            isSymmetric(left->left, right->right) &&
            isSymmetric(left->right, right->left);
    }
};
