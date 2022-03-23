/*
          https://leetcode.com/problems/string-to-integer-atoi/

    1. Read in and ignore any leading whitespace.
    2. Check if the next character (if not already at the end of the string) is '-' or '+'.
       Read this character in if it is either. This determines if the final result is negative or positive respectively.
       Assume the result is positive if neither is present.
    3. Read in next the characters until the next non-digit character or the end of the input is reached.
       The rest of the string is ignored.
    4. Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32).
       If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
    5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
       then clamp the integer so that it remains in the range. Specifically, integers less than -2^31 should be clamped to -2^31,
       and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const string max_int_s = "2147483647";
const string min_int_s = "2147483648";    // abs value, minus sign is assumed
constexpr int max_int = 2147483647;
constexpr int min_int = -2147483648;

int myAtoi(const string& s)
{
    if (s.empty()) return 0;

    int n{ 0 };
    bool sign{ false };
    size_t len{ s.length() };
    size_t cur_pos{ s.find_first_not_of(' ') };

    if (cur_pos >= len) return 0;

    // deal with the sign and chech if there are digits left
    if (s[cur_pos] == '-' || s[cur_pos] == '+') {
        sign = s[cur_pos] == '-';
        ++cur_pos;
    }
    // skip leading zeroes
    while (cur_pos < len && s[cur_pos] == '0') {
        ++cur_pos;
    }
   // calc length of the number and deal with out of range numbers
    size_t j{ cur_pos };
    while (j < len && isdigit(s[j])) ++j;
    size_t num_len = j - cur_pos;
    if (num_len > max_int_s.length()) {
        return sign
            ? min_int
            : max_int;
    }
    if (num_len == max_int_s.length()) {
        const string& boundary = sign
            ? min_int_s
            : max_int_s;
        bool is_outta_range{ true };
        for (size_t i{ 0u }; i < num_len; ++i) {
            if (s[cur_pos + i] < boundary[i]) {
                is_outta_range = false;
                break;
            }
            if (s[cur_pos + i] > boundary[i]) break;
        }
        if (is_outta_range)
            return sign ? min_int : max_int;
    }
    // parse the number
    while (cur_pos < len && isdigit(s[cur_pos])) {
        n *= 10;
        n += s[cur_pos] - '0';
        ++cur_pos;
    }
    return sign ? -n : n;
}

//============================================================================//

int main ()
{
    string s;
    while (true) {
        cout << "Input, please!\n";
        string s;
        cin >> s;
        cout << "Here's your integer:\n" << myAtoi(s) << '\n';
    }    
    return 0;
}
