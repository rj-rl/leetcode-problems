/*
  https://leetcode.com/problems/swapping-nodes-in-a-linked-list/

  You are given the head of a linked list, and an integer 'k'.
  Return the head of the linked list after swapping the values of the kth node from the beginning
  and the kth node from the end (the list is 1-indexed)
/**/

#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* make_list(string str)
{
    auto dummy_head = new ListNode();
    auto cur = dummy_head;
    for (auto digit : str) {
        auto new_one = new ListNode(digit - '0');
        cur->next = new_one;
        cur = new_one;
    }
    return dummy_head->next;
}

void print(ListNode* head)
{
    while (head) {
        cout << head->val << "->";
        head = head->next;
    }
}

int size(ListNode* head)
{
    int sz = 0;
    while (head) {
        ++sz;
        head = head->next;
    }
    return sz;
}

ListNode* swapNodes(ListNode* head, int k)
{
    int sz = size(head);
    if (sz < k) return nullptr;
    
    int mid = (sz + 1) / 2;
    if (sz % 2  &&  k == mid ) return head;

    int left = k;
    int right = sz - (k - 1);  // because of the 1-indexing
    if (left > right) {
        swap(left, right);
    }

    ListNode* first_node = head;
    for (int i = 1; i < left; ++i) {
        first_node = first_node->next;
    }
    ListNode* second_node = first_node;
    for (int i = left; i < right; ++i)
    {
        second_node = second_node->next;
    }
    swap(first_node->val, second_node->val);

    return head;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the list:\n";
        string list;
        cin >> list;
        auto head = make_list(move(list));

        cout << "Enter the position k:\n";
        int k {};
        cin >> k;

        auto modified = swapNodes(head, k);
        cout << "Here's the same list with positions k and k-from-end swapped:\n";
        print(modified);
        cout << '\n';
    }
    return 0;
}
