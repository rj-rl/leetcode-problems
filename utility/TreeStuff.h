/*
  The definition of a binary tree node and an assortment
  of utility functions related to binary trees
/**/

#include <iostream>
#include <queue>
#include <string>
#include <sstream>

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

// returns root of a binary tree constructed from string
// the string is presumed to contain nodes of the tree
// in breadth-first order
inline TreeNode* from_string(const std::string& str)
{
    std::istringstream input{ str };
    std::string node_str;

    input >> node_str;
    TreeNode* root = new TreeNode(std::stoi(node_str));
    std::queue<TreeNode*> queue;
    queue.push(root);

    while (true) {
        auto node = queue.front();
        queue.pop();

        if (!(input >> node_str)) {
            break;
        }
        if (node_str != "null") {
            node->left = new TreeNode(std::stoi(node_str));
            queue.push(node->left);
        }
        if (!(input >> node_str)) {
            break;
        }
        if (node_str != "null") {
            node->right = new TreeNode(stoi(node_str));
            queue.push(node->right);
        }
    }
    return root;
}

// prints a binary tree
inline void print_BT(
    const TreeNode* node,
    const std::string& prefix,
    bool is_right,
    bool is_first = false,
    std::ostream& out = std::cout)
{
    if (!node) return;
    out << prefix;

    if (is_first) {
        out << "    ";
    }
    else {
        out << (is_right ? "├──" : "└──" );
    }
    // print the value of the node
    out << node->val << '\n';

    // enter the next tree level - right and left branch
    print_BT(node->right, prefix + (is_right ? "│   " : "    "),  true);
    print_BT(node->left,  prefix + (is_right ? "│   " : "    "), false);
}

inline void print_BT(const TreeNode* node)
{
    print_BT(node, "", false, true);
}
