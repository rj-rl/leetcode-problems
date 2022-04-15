/*
  https://leetcode.com/problems/regular-expression-matching/
  Given an input string 's' and a pattern 'p', implement regular expression
  matching with support for '.' and '*' where:
    '.' matches any single character
    '*' matches zero or more of the preceding element
  The matching should cover the entire input string (not partial)
/**/

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool isMatch(string s, string p)
{
    int p_size = p.size();
    int s_size = s.size();
    // 'memo[i][j]' is whether 'p[i:]' matches 's[j:]'
    // where 's[i:]' is 's' from ith char onwards
    // for convenience we add one extra row and column
    vector<vector<bool>> memo (p_size + 1, vector<bool>(s_size + 1, false));

    // can we match 'p[k:]' with empty string?
    // if all tokens in 'p[k:]' are '...*' then yes
    // as soon as we see another token, then no for the rest of 'k' >= 0
    for (int k = p_size - 1; k >= 0; --k) {
        if (p[k] == '*') {
            memo[k - 1][s_size] = true;
            // skip another row, since '...*' is a single token but two chars
            // so it takes up two rows while being semantically one
            --k;
        }
        else break;
    }
    memo[p_size][s_size] = true; // two empty strings match each other

    for (int i = p_size - 1; i >= 0; --i) {
        for (int j = s_size - 1; j >= 0; --j) {

            if (p[i] == '*') {
                bool is_asterisk_match = (p[i - 1] == s[j]) || (p[i - 1] == '.');
                // i-1 because '...*' is a single token but two chars
                memo[i - 1][j]
                    = is_asterisk_match && memo[i - 1][j + 1]  // use '...*' 1 or more times
                    || memo[i + 1][j];  // use '...*' token 0 times
            }
            else {
                bool is_literal_or_dot_match = (p[i] == s[j]) || (p[i] == '.');
                memo[i][j] = is_literal_or_dot_match && memo[i + 1][j + 1];
            }
        }
        if (p[i] == '*') --i;  // after dealing with '...*', skip its second row (single token, 2 chars)
    }

    return memo[0][0];
}

//===========================================================================//

int main()
{
    while (true) {
        cout << "Enter the string:\n";
        string s;
        cin >> s;
        cout << "And the regex pattern:\n";
        string p;
        cin >> p;

        if (isMatch(move(s), move(p))) {
            cout << "The pattern matches the string!\n";
        }
        else {
            cout << "Not a match, mate\n";
        }
    }
    return 0;
}
