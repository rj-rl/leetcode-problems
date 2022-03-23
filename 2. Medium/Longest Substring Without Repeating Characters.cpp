//==============================================================================//
//                                                                              //
// https://leetcode.com/problems/longest-substring-without-repeating-characters //
//                                                                              //
//==============================================================================//

#include <iostream>
#include <string>

using namespace std;

int lengthOfLongestSubstring(const string& s)
{
    bool contains[256] = {};
    size_t n = s.length();
    int l = 0, r = 0;
    int max = 0;

    while (r < n) {
        if (contains[s[r]]) {
            while (contains[s[r]]) {
                contains[s[l]] = false;
                ++l;
            }
        }
        contains[s[r]] = true;
        ++r;
        max = std::max(max, r - l);
    }
    return max;
}

//============================================================================//

int main()
{
    string s;
    while (true) {
        cout << "Please enter a string:\n";
        cin >> s;
        cout << "Length of the longest substring without repeating chars is "
            << lengthOfLongestSubstring(s) << '\n';
    }
    return 0;
}
