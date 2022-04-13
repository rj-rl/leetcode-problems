/*
  https://leetcode.com/problems/longest-valid-parentheses/

  Given a string containing just the characters '(' and ')',
  return the length of the longest valid (well-formed) parentheses substring
/**/

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

// pop and return top element
int pop_top(stack<int>& stack)
{
    int top = stack.top();
    stack.pop();
    return top;
}

// collapses positive numbers on top of the stack into their sum and returns it
int squish(stack<int>& stack)
{
    int sum = 0;
    while (!stack.empty() && stack.top() > 0) {
        sum += pop_top(stack);
    }
    stack.push(sum);
    return sum;
}

int longestValidParentheses(const string& str)
{
    // -1 encodes '(', numbers are lengths of partial expressions;
    // for example, input ((()()(()( becomes
    // -1 < top
    //  2
    // -1
    //  4
    // -1
    // -1 < bottom
    stack<int> history;
    int max_len = 0;

    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '(') {
            history.push(-1);
            continue;
        }

        if (str[i] == ')') {
            if (history.empty()) continue;

            auto top = pop_top(history);
            if (top == -1) {
                history.push(2);
            }
            else {  // subexpression length was on top
                if (history.empty()) continue;
                history.pop();  // guaranteed to be -1 aka '(' at this point
                history.push(top + 2);
            }
            auto len = squish(history);
            max_len = max(max_len, len);
        }
    }

    return max_len;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the string:\n";
        string str;
        cin >> str;

        cout << "The max length of parentheses expression within the string is:\n"
            << longestValidParentheses(str) << '\n';
    }

    return 0;
}
