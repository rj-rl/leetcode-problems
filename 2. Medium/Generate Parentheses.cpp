// https://leetcode.com/problems/generate-parentheses/

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

// converts numeric 'pattern' to string: 1 is '(' and 0 is ')'
// for example: 10 -> '()',  110100 -> '(()())'
string interpret_pattern(uint64_t pattern)
{
    string result;
    while (pattern > 0) {
        bool is_opening_parenthesis = pattern % 10;
        pattern /= 10;
        if (is_opening_parenthesis) result.push_back('(');
        else result.push_back(')');
    }
    reverse(begin(result), end(result));
    return result;
}

// 'open_count' and 'close_count' is how many '(' and ')' we have to spend
// 'pattern' encodes the parentheses done so far as a number
void recursive_parentheses(vector<string>& result,
                           uint64_t pattern, 
                           int open_count, 
                           int close_count)
{
    // stop condition: everything's spent, we're done
    if (open_count == 0 && close_count == 0) {
        result.push_back(interpret_pattern(pattern));
        return;
    }

    // invalid expression condition
    if (open_count > close_count) return;

    // parentheses are balanced so far, this means next one has to be '('
    if (open_count == close_count) {
        // 'pattern * 10 + 1' appends a 1 to our 'pattern', i.e. adds a '('
        recursive_parentheses(result, pattern * 10 + 1, open_count - 1, close_count);
        return;
    }
	
    // in this case both options are viable (but we may have run out of '('s, gotta check)
    if (open_count < close_count) {
        if (open_count > 0) {
            recursive_parentheses(result, pattern * 10 + 1, open_count - 1, close_count);
        }
        // 'pattern * 10' appends a 0
        recursive_parentheses(result, pattern * 10, open_count, close_count - 1);
        return;
    }
}

vector<string> generateParenthesis(int n)
{
    vector<string> result;
    // 'pattern' starts as 1 because any valid expression starts with '('
    // since we start with '(' there's 'n-1' of them left
    // haven't yet spent any ')', 'n' of those
    recursive_parentheses(result, 1, n - 1, n);

    return result;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter n:\n";
        int n {};
        cin >> n;

        auto valid_paren = generateParenthesis(n);
        cout << "Here's all the valid parentheses\n";
        for (auto& combo : valid_paren) {
            cout << combo << '\n';
        }
    }
    return 0;
}
