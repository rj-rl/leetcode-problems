//==============================================================================================//
//                                                                                              //
//			https://leetcode.com/problems/longest-substring-without-repeating-characters/		//
//                                                                                              //
//==============================================================================================//

#include <iostream>
#include <string>

using std::string;

int lengthOfLongestSubstring(string s)
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
    
int main() {
	string s;
	while(true) {
		std::cout << "Please enter a string:\n";
		std::cin >> s;
		std::cout << lengthOfLongestSubstring(s) << '\n';
	}

	return 0;
}
