/*
  https://leetcode.com/problems/binary-search-tree-iterator/

  Implement the 'BSTIterator' class that represents an iterator
  over the in-order traversal of a binary search tree
/**/

#include <iostream>
#include <stack>
#include <cassert>
#include "../utility/TreeStuff.h"

using namespace std;

class BSTIterator {
public:
    BSTIterator(TreeNode* root)
    {
        go_left(root);
    }

    int next()
    {
        assert(hasNext());
        auto cur = in_order_.top();
        in_order_.pop();
        go_left(cur->right);
        return cur->val;
    }

    bool hasNext()
    {
        return !in_order_.empty();
    }

private:
    stack<TreeNode*> in_order_;

    // traverses as far to the left of the 'node' as possible
    // stacks all the visited nodes, including the 'node' itself
    void go_left(TreeNode* node)
    {
        while (node) {
            in_order_.push(node);
            node = node->left;
        }
    }
};

//===========================================================================//

int main()
{
    while (true) {
        cout << "Enter the binary search tree "
            << "in the breadth-first order please!\n";
        string input;
        getline(cin, input);
        auto root = from_string(input);

        cout << "Here's your tree\n";
        print_BT(root);

        BSTIterator it(root);
        cout << "What do we wanna do now? Type 'n' to advance iterator, "
            << "type 'hn' to see if next position exists, type 's' to stop\n";

        while (true) {
            string command;
            cin >> command;
            if (command == "n") {
                cout << it.next() << '\n';
            }
            else if (command == "hn") {
                cout << (it.hasNext()
                    ? "Next position exists\n"
                    : "Next position doesn't exist\n");
            }
            else break;
        }
        cin.ignore();
        cout << '\n';
    }
    return 0;
}
