/*
  https://leetcode.com/problems/reverse-nodes-in-k-group/

  Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

  k is a positive integer and is less than or equal to the length of the linked list.
  If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

  You may not alter the values in the list's nodes, only nodes themselves may be changed.
/**/

#include <iostream>

struct ListNode {
    int       val;
    ListNode* next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* reverseKGroup(ListNode* head, int k)
{
    if (!head) return nullptr;
    
    ListNode* cur = head;
    ListNode* prev = nullptr;
    int i = 0;

    while (cur && (i < k)) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        ++i;
    }
    
    if (i < k) {    // undo the very last bit
        while (i) {
            ListNode* next = prev->next;
            prev->next = cur;
            cur = prev;
            prev = next;
            --i;
        }
        return head;
    }
    
    head->next = reverseKGroup(cur, k);
    return prev;
}

void printList(const ListNode* head)
{
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
}

void cleanup(ListNode* head)
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
        ListNode* head = new ListNode();
        ListNode* cur = head;
        int k{ 0 };
        
        std::cin >> n;
        std::cin >> head->val;
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
