/*
  https://leetcode.com/problems/merge-k-sorted-lists/

  You are given an array of 'k' linked-lists 'lists', each one is sorted in ascending order.
  Merge all the linked-lists into one sorted linked-list and return it
/**/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int       val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* read_list(istream& in)
{
    int x{};
    auto dummy_head = new ListNode();
    auto cur = dummy_head;

    while (in >> x) {
        auto next = new ListNode(x);
        cur->next = next;
        cur = next;
    }
    in.clear();
    in.ignore();

    auto actual_head = dummy_head->next;
    delete dummy_head;
    return actual_head;
}

void printList(const ListNode* head)
{
    while (head) {
        cout << head->val << ' ';
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

template <class Iterator>
void cleanup(Iterator begin, Iterator end)
{
    while (begin != end) {
        cleanup(*begin++);
    }
}

//============================================================================//

template <class BinaryOp>
struct ListCmp {
    ListCmp()
        : op_ {}
    {
    }

    bool operator()(ListNode* left, ListNode* right)
    {
        return op_(left->val, right->val);
    }
    BinaryOp op_;
};

ListNode* mergeKLists(vector<ListNode*>& lists)
{
    if (lists.empty()) return nullptr;

    priority_queue<
        ListNode*,
        vector<ListNode*>,
        ListCmp<greater<int>>
    > queue{};

    for (auto list : lists) {
        if (list) queue.push(list);
    }

    auto dummy_head = new ListNode();
    auto cur = dummy_head;

    while (!queue.empty()) {
        auto smallest = queue.top();
        queue.pop();
        if (smallest->next != nullptr) {
            queue.push(smallest->next);
        }

        auto next = new ListNode(smallest->val);
        cur->next = next;
        cur = next;
    }

    auto actual_head = dummy_head->next;
    delete dummy_head;
    return actual_head;
}

//============================================================================//

int main ()
{
    while (true) {
        cout << "How long is the array?\n";
        int n{};
        cin >> n;

        vector<ListNode*> lists;
        while (n-- > 0) {
            lists.push_back(read_list(cin));
        }

        cout << "Here's your lists merged:\n";
        auto merged = mergeKLists(lists);
        printList(merged);
        cout << '\n';

        cleanup(merged);
        cleanup(begin(lists), end(lists));
    }

    return 0;
}
