/*
  https://leetcode.com/problems/kth-smallest-element-in-a-bst/

  Given the root of a binary search tree, and an integer 'k',
  return the 'k'th smallest value (1-indexed) of the nodes of the tree
/**/

#include <iostream>
#include <stack>
#include "../utility/TreeStuff.h"

using namespace std;

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

//===========================================================================//

int main()
{
    while (true) {
        cout << "Enter the binary search tree "
            << "in the breadth-first order please!\n";
        string input;
        getline(cin, input);
        auto root = from_string(input);

        cout << "Enter k\n";
        int k{ };
        cin >> k;
        // since we use both operator>> and getline, we need to ignore the
        // newline char, because operator>> gladly leaves it in the buffer for
        // getline to read a string that is a single '\n' right after
        cin.ignore();

        cout << "Here's your tree\n";
        print_BT(root);
        cout << "And here's the Kth smallest element\n"
            << kthSmallest(root, k) << '\n';
    }
    return 0;
}
