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

using namespace std;

bool isMatch(string s, string p)
{
    // reached the end simultaneously - we have a match!
    if (s.empty() && p.empty()) return true;
    // pattern is exhausted but string is not - mismatch
    if (!s.empty() && p.empty()) return false;

    bool is_first_char_match
        = !s.empty() && (s.front() == p.front() || p.front() == '.');

    if (p.length() > 1 && p[1] == '*') {
        return isMatch(s, p.substr(2))  // this means * pattern is not used at all and is discarded
            || is_first_char_match && isMatch(s.substr(1), p);  // this means * is used >= 1 times
    }
    else return is_first_char_match && isMatch(s.substr(1), p.substr(1));
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
