//============================================================================//
//                                                                            //
//        https://leetcode.com/problems/longest-palindromic-substring         //
//                                                                            //
//============================================================================//

#include <iostream>
#include <string>
#include <map>

using namespace std;

// symmetrically grows a palindrome in 's' given by two indices: from 'from' to (and including) 'to'
// until it ceases to be palindromic, returns maximal palindrome reached
string grow(int from, int to, const string& s)
{
    while (from >= 0 && to < (int)s.length()) {
        if (s[from] != s[to]) break;
        --from;
        ++to;
    }
    return s.substr(from + 1, to - (from + 1));
}

/* 
Any palindrome within 's' must have a nucleus which is either a single character or a pair of chars
(depening on if the palindrome has an odd or even length). We scan through 's' and grow palindromes starting
in every such nucleus, resulting in O(N^2) time complexity
*/
string longestPalindrome(const string& s)
{
    map<int, string> palindromes;

    for (int i = 0; i < (int)s.length(); ++i) {
        string pal = grow(i, i, s);
        palindromes[pal.length()] = std::move(pal);

        if (i > 0 && s[i - 1] == s[i]) {
            pal = grow(i - 1, i, s);
            palindromes[pal.length()] = std::move(pal);
        }
    }

    return palindromes.rbegin()->second;
}

//============================================================================//

int main ()
{
    while (true) {
        string input;
        cout << "Please enter a string:\n";
        cin >> input;
        cout << "Longest detected palindrome:\n" << longestPalindrome(input) << '\n';
    }
    return 0;
}
