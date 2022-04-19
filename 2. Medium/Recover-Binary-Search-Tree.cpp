/*
  https://leetcode.com/problems/recover-binary-search-tree/

  Given the root of a binary search tree, where the values of exactly two nodes
  were swapped by mistake, recover the tree without changing its structure
/**/

#include <iostream>
#include <stack>
#include <utility>
#include "../utility/TreeStuff.h"

using namespace std;

void recoverTree(TreeNode* root)
{
    // the two perpertrators
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;

    stack<TreeNode*> to_do;
    TreeNode* cur = root;
    TreeNode* prev = nullptr;
    while (!to_do.empty() || cur) {
        while (cur) {
            to_do.push(cur);
            cur = cur->left;
        }

        cur = to_do.top();
        to_do.pop();
        if (prev && cur->val < prev->val) {
            if (!first) first = prev;
            second = cur;
        }
        prev = cur;
        cur = cur->right;
    }

    if (first && second) {
        swap(first->val, second->val);
    }
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

        cout << "Here's the broken tree\n";
        print_BT(root);

        cout << "And here's your tree fixed\n";
        recoverTree(root);
        print_BT(root);
        cout << '\n';
    }
    return 0;
}
