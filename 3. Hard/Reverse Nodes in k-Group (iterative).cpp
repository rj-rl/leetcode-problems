/*
          https://leetcode.com/problems/reverse-nodes-in-k-group/

    Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

    k is a positive integer and is less than or equal to the length of the linked list.
    If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

    You may not alter the values in the list's nodes, only nodes themselves may be changed.
*/

#include <iostream>
#include <utility>

struct ListNode {
    int       val;
    ListNode* next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// returns head of inverted group and first link of next, unprocessed group
std::pair<ListNode*, ListNode*> processGroup(ListNode* head, int k)
{
    ListNode* prev = nullptr;
    ListNode* cur = head;
    
    while (cur && k) {
        auto next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        --k;
    }

    if (k) {    // if the group had less than k nodes, gotta unreverse it
        auto cur = prev;
        prev = nullptr;
        while( cur ) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return { head, nullptr };
    }
    return { prev, cur };
}

ListNode* reverseKGroup(ListNode* head, int k)
{
    ListNode* cur = head;
    ListNode* new_head = head;
    ListNode* prev_batch_tail = nullptr;
    bool is_first_batch = true;
    
    while (cur) {
        auto batch_new_tail = cur;
        auto [batch_new_head, next_batch_start] = processGroup(cur, k);
        if (is_first_batch) {
            new_head = batch_new_head;
            is_first_batch = false;
        }
        else {
            prev_batch_tail->next = batch_new_head;
        }
        prev_batch_tail = batch_new_tail;
        cur = next_batch_start;
    }
    return new_head;
}

void printList(const ListNode* head)
{
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
}

void cleanup(const ListNode* head)
{
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

int main ()
{
    while (true) {
        std::cout << "Input, please! List length, followed by elements, followed by group size:\n";
        size_t n{ 0 };
        std::cin >> n;
        ListNode* head = new ListNode();
        ListNode* cur = head;
        std::cin >> head->val;
        int k{ 0 };
        
        while (n-- > 1) {
            int x;
            std::cin >> x;
            ListNode* next = new ListNode(x);
            cur->next = next;
            cur = next;
        }
        std::cin >> k;
        printList(reverseKGroup(head, k));
        std::cout << '\n';
        cleanup(head);
    }
    return 0;
}
