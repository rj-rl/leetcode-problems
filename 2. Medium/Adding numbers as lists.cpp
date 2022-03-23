//==============================================================================================//
//                                                                                              //
//                            https://leetcode.com/problems/add-two-numbers/                    //
//                                                                                              //
//==============================================================================================//

#include <iostream>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    ListNode(string& str)
        : next{ nullptr }
    {
        val = str[0] - '0';
        ListNode* cur = this;
        for (size_t i = 1u; i < str.length(); ++i) {
            int x = str[i] - '0';
            auto new_node = new ListNode(x);
            cur->next = new_node;
            cur = new_node;
        }
    }

    // UTILITY FUNC
    void print() const
    {
        cout << val << "->";
        auto cur = this;
        while (cur->next) {
            cur = cur->next;
            cout << cur->val << "->";
        }
    }
};

// prints a number stored as a list of digits in reverse order
void print_as_n(ListNode* l)
{
    if (l->next) {
        print_as_n(l->next);
    }
    cout << l->val;
}

// REGULAR VERSION
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    bool carry{ false };
    int sum{ 0 };
    // dummy_head needed for convenient return
    ListNode* dummy_head = new ListNode();
    ListNode* cur = dummy_head;

    while (l1 || l2) {
        int a, b;
        a = l1 ? l1->val : 0;
        b = l2 ? l2->val : 0;
        sum = a + b + carry;
        carry = sum / 10;
        cur->next = new ListNode(carry ? sum % 10 : sum);

        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    if (carry) {
        cur->next = new ListNode(1);
    }
    return dummy_head->next;
}

void add_recursive(ListNode* l1, ListNode* l2, bool carry, ListNode* cur)
{
    if (!l1 && !l2 && !carry) {	// stop condition
        return;
    }
    int sum{ carry };
    if (l1) {
        sum += l1->val;
        l1 = l1->next;
    }
    if (l2) {
        sum += l2->val;
        l2 = l2->next;
    }
    carry = sum > 9;
    ListNode* new_node = new ListNode(carry ? sum - 10 : sum);
    cur->next = new_node;
    add_recursive(l1, l2, carry, new_node);
}

// RECURSIVE VERSION
ListNode* addTwoNumbersRec(ListNode* l1, ListNode* l2)
{
    int sum{ l1->val + l2->val };
    bool carry{ sum > 9 };
    ListNode* head = new ListNode(carry ? sum - 10 : sum);
    add_recursive(l1->next, l2->next, carry, head);

    return head;
}

//================================================================================================

int main()
{
    while (true) {
        string s;
        cout << "Enter list1:\n";
        getline(cin, s);
        ListNode list1(s);
        cout << "Enter list2:\n";
        getline(cin, s);
        ListNode list2(s);

        cout << "Numbers ";
        print_as_n(&list1);
        cout << " and ";
        print_as_n(&list2);
        cout << " add up to ";
        print_as_n(addTwoNumbers(&list1, &list2));
        cout << '\n';
    }
    return 0;
}
