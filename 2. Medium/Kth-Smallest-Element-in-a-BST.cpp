/*
  https://leetcode.com/problems/kth-smallest-element-in-a-bst/

  Given the root of a binary search tree, and an integer 'k',
  return the 'k'th smallest value (1-indexed) of the nodes of the tree
/**/

#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode()
        : val(0), left(nullptr), right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x), left(nullptr), right(nullptr)
    {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right)
    {
    }
};

    int kthSmallest_iterative(TreeNode* root, int k) {
        stack<TreeNode*> stack;
        while (!stack.empty() || root) {
            while (root) {
                stack.push(root);
                root = root->left;
            }
            root = stack.top();
            stack.pop();
            if (--k == 0) return root->val;
            root = root->right;
        }
        return -1;
    }

    // below is recursive version
    // LNR is for left-node-root, aka in-order traversal
    int LNR(TreeNode* root, int& k) {
        if (!root) return 0;
        int result = 0;
        
        result += LNR(root->left, k);
        --k;
        if (k == 0) return root->val;
        if (k < 0)  return result;
        result += LNR(root->right, k);
        
        return result;
    }
    
    int kthSmallest(TreeNode* root, int k) {
        return LNR(root, k);
    }

//==============================================================================================//

int main()
{
    return 0;
}
