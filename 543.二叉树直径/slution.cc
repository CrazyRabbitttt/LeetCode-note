/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int res = 0;
    int diameterOfBinaryTree(TreeNode* root) {
        //递归：相信函数能够帮我们完成工作
        postOrder(root);
        return res;
    }

    int postOrder(TreeNode* node) {
        //因为从根节点开始，我们需要字节点的状态，所以是后续便利
        if (node == nullptr) return 0;
        if (node->left == nullptr || node->right == nullptr) {
            //子树直接就能确定了
            if (node->left == nullptr && node->right == nullptr) 
                return 0;
            if (node->left == nullptr) {        //right not null
                int rightMax = postOrder(node->right);
                res = max(res, rightMax + 1);
                return 1 + rightMax;
            } else {
                int leftMax = postOrder(node->left);
                res = max(res, leftMax + 1);
                return 1 + leftMax;
            }
        }

        //不是的话，要比较左右紫薯了
        int leftMax = postOrder(node->left);
        int rightMax = postOrder(node->right);

        //➕2是因为将左子树、右子树、根节点当作是一条直径了，当然这不是返回的数
        res = max(res, leftMax + rightMax + 2);

        return 1 + max(leftMax, rightMax);
    }


};