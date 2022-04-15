/*
  https://leetcode.com/problems/trim-a-binary-search-tree/

  Given the 'root' of a binary search tree and two numbers 'low' and 'high',
  trim the tree so that all its elements lie in '[low, high]'.
  Trimming the tree should not change the relative structure of its elements,
  i.e. any node's descendant should remain a descendant.
  It can be proven that there is a unique answer

  Return the root of the trimmed binary search tree;
  note that the root may change depending on the given bounds
/**/

#include <iostream>

using namespace std;

struct TreeNode {
     int val;
     TreeNode* left;
     TreeNode* right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* trimBST(TreeNode* root, int low, int high)
{
// find the tallest tree with 'root' in '[low, high]'
    while (root) {
        if (root->val < low) {
            root = root->right;
            continue;
        }
        else if (root->val > high) {
            root = root->left;
        }
        else break;
    }
    if (!root) return nullptr;

    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

//==============================================================================================//

int main()
{
    //   КАРТИНУ  
    //  НАПИСАТЬ  
    //     🚀    
    //  НЕ УСПЕЛ  
}
