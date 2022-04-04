/*
  https://leetcode.com/problems/valid-palindrome-ii
/**/

#include <iostream>
#include <string>
#include <utility>

using namespace std;

bool isPalindrome(const string& s, int left, int right)
{
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

bool validPalindrome(string s)
{
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return isPalindrome(s, left + 1, right)
                || isPalindrome(s, left, right - 1);
        }
        ++left;
        --right;
    }
    return true;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the string to check:\n";
        string s;
        cin >> s;

        if (validPalindrome(move(s))) {
            cout << "The string is a palindrome (possibly gotta remove one char though)\n";
        }
        else {
            cout << "The string ain't a palindrome even with one deletion allowed\n";
        }
    }
    return 0;
}
