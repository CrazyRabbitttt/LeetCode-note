class Solution {
public:
    int ans;
    int dfs(TreeNode* root){
        if(!root)return 0;
        const int l = dfs(root->left), r = dfs(root->right);
        const int lp = (root->left && root->left->val == root->val) ? l : 0;
        const int rp = (root->right && root->right->val == root->val) ? r : 0;
        ans = max(ans, lp + rp);
        return max(lp, rp) + 1;
    }
    int longestUnivaluePath(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
