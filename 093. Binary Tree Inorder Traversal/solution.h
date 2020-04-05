#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        stack<TreeNode *> s;
        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            } else {
                TreeNode* n = s.top(); s.pop();
                ret.push_back(n->val);
                root = n->right;
            }
        }
        return ret;
    }

    //前序的一个应用就是计算表达式，前序遍历得到序列（保存到栈中）+/*23-21*3-41，再从右至左取数，直到取到操作符，就将刚才取
    //到的2个数用该操作符计算，结果再回填至栈顶。直到栈中只剩一个元素即为结果。
    //后序也是一样，只是扫描方向相反，从左至右扫描即可。
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> v;
        if (!root) return v;
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* n = s.top(); s.pop();
            v.push_back(n->val);
            if (n->right) { //先进右子树
                s.push(n->right);
            }
            if (n->left) {
                s.push(n->left);
            }
        }
        return v;
    }

    vector<int> postorderTraversal1(TreeNode *root) {
        vector<int> v;
        if (!root) return v;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()){
            TreeNode *n = s.top(); s.pop();
            v.push_back(n->val);
            if (n->left){
                s.push(n->left);
            } 
            if (n->right) {
                s.push(n->right);
            }
        }
        std::reverse(v.begin(), v.end());  // the trick
        return v;
    }

    // traditional and standard way.
    // using the stack to simulate the recursive function stack.
    vector<int> postorderTraversal2(TreeNode *root) {
        vector<int> v;
        stack<TreeNode*> s;
        TreeNode *lastVisitNode = NULL;
        while (root || !s.empty()){
            if (root) {
                // keep going the left
                s.push(root);
                root = root->left;
            } else {
                TreeNode *n = s.top();
                // left way is finsised, keep going to the right way
                if (n->right && lastVisitNode != n->right){
                    root = n->right;
                } else {
                    // both left and right has been accessed.
                    s.pop();
                    v.push_back(n->val);
                    lastVisitNode = n;
                }
            }
        }
        return v;
    }

    vector<int> levelOrderTraversal(TreeNode* root) {
        vector<int> v;
        if (!root) return v;
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            TreeNode *n = q.front(); q.pop_front();
            v.push_back(n->val);
            if(n->left) {
                q.push_back(n->left);
            }
            if(n->right) {
                q.push_back(n->right);
            }
        }
        return v;
    }

    /********************************************************************************** 
    * 
    * Given a binary tree, return the level order traversal of its nodes' values. 
    * (ie, from left to right, level by level).
    * 
    * For example:
    * Given binary tree {3,9,20,#,#,15,7},
    * 
    *     3
    *    / \
    *   9  20
    *     /  \
    *    15   7
    * 
    * return its level order traversal as:
    * 
    * [
    *   [3],
    *   [9,20],
    *   [15,7]
    * ]
    * 
    * confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
    * 
    * OJ's Binary Tree Serialization:
    * 
    * The serialization of a binary tree follows a level order traversal, where '#' signifies 
    * a path terminator where no node exists below.
    * 
    * Here's an example:
    * 
    *    1
    *   / \
    *  2   3
    *     /
    *    4
    *     \
    *      5
    * 
    * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}". 
    * 
    *               
    **********************************************************************************/
    vector<vector<int> > levelOrder3(TreeNode *root) {
        vector< vector<int> > vv;
        if(root == NULL) return vv;

        int level = 0; // current level.
        TreeNode *last = root; // last node of currrent level.
        queue<TreeNode*> q;
        q.push(root);
        vv.push_back(vector<int>());
        while (!q.empty()) {
            TreeNode *n = q.front(); q.pop();
            vv[level].push_back(n->val);
            if (n->left)
                q.push(n->left);
            if (n->right)
                q.push(n->right);

            if (n == last) {
                level++;
                last = q.back();
                vv.push_back(vector<int>()); // new buffer for next row.
            }
        }
        vv.pop_back();

        return vv;
    }


};
