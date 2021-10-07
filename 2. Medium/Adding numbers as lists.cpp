//==============================================================================================//
//                                                                                              //
//			https://leetcode.com/problems/add-two-numbers/				//
//                                                                                              //
//==============================================================================================//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <stdexcept>
#include <bitset>
#include <random>

using namespace std;

//================================================================================================

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	ListNode(string& vec)
		: next {nullptr}
	{
		val = vec.back() - '0';
		vec.pop_back();
		ListNode* cur = this;

		while (!vec.empty()) {
			int x = vec.back() - '0';
			vec.pop_back();
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

// UTILITY FUNC
void print_as_n(ListNode* l)
{
	if (l->next) {
		print_as_n(l->next);
	}
	cout << l->val;
}

// REGULAR VERSION
ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2)
{
	bool carry {false};
	int sum {0};
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
	int sum {carry};
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
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	int sum {l1->val + l2->val};
	bool carry {sum > 9};
	ListNode* head = new ListNode(carry ? sum - 10 : sum);
	add_recursive(l1->next, l2->next, carry, head);
	
	return head;
}

//================================================================================================
//================================================================================================

int main()
{
	string s;
	cout << "enter list1:\n";
	getline(cin, s);
	ListNode l1(s);
	cout << "enter list2:\n";
	getline(cin, s);
	ListNode l2(s);
	
	cout << "\nTEST RESULT:\n";
	print_as_n(addTwoNumbers(&l1, &l2));

	return 0;
}
