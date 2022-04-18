/*
  https://leetcode.com/problems/convert-bst-to-greater-tree/

  Given the root of a binary search tree (BST), convert it to a 'greater tree',
  meaning every key of the original BST is itself key plus the sum of all keys
  greater than itself
/**/

#include <iostream>
#include <stack>
#include <string>
#include "../utility/TreeStuff.h"

using namespace std;

// reverse in-order traversal:
// right-node-left
// 'sum' is the sum of elements greater than root
// returns sum of subtree elements with root in 'root'
int RIOT(TreeNode* root, int sum) {
    if (!root) return sum;

    sum = RIOT(root->right, sum);
    int old_val = root->val;
    root->val += sum;
    sum = RIOT(root->left, sum+old_val);
    return sum;
}

TreeNode* convertBST2(TreeNode* root) {
    RIOT(root, 0);
    return root;
}

TreeNode* convertBST(TreeNode* root) {
    if (!root) return nullptr;
    
    stack<TreeNode*> to_do;
    to_do.push(root);
    int greater_sum = 0;
    bool is_right_done = false;
    
    while(!to_do.empty()) {
        auto subroot = to_do.top();
        auto right = subroot->right;
        auto left  = subroot->left;
        
        if (right && !is_right_done) {
            to_do.push(right);
            continue;
        }            
        else {
            int old_val = subroot->val;
            subroot->val += greater_sum;
            greater_sum += old_val;
            to_do.pop();
            is_right_done = true;
            if (left) {
                to_do.push(subroot->left);
                is_right_done = false;
            }
        }
    }
    return root;
}

//===========================================================================//

int main()
{
    while (true) {
        cout << "Enter the tree in the breadth-first order please!\n";
        string input;
        getline(cin, input);
        auto root = from_string(input);

        cout << "Here's your tree\n";
        print_BT(root);

        auto greater_tree = convertBST(root);
        cout << "And here's your tree converted to a 'greater tree'\n";
        print_BT(greater_tree);
    }
    return 0;
}
