/*
          https://leetcode.com/problems/reverse-integer/

  Given a signed 32-bit integer 'x', return 'x' with its digits reversed.
  If reversing 'x' causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

  Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
*/

#include <iostream>

using namespace std;

constexpr int int32_min = 0b1000'0000'0000'0000'0000'0000'0000'0000;
constexpr int int32_max = 0b0111'1111'1111'1111'1111'1111'1111'1111;

int reverse(int x)
{
    int reversed = 0;
    while (x) {
        int cur_digit = x % 10;
        x /= 10;

        if (reversed > int32_max / 10
            || reversed == int32_max / 10 && cur_digit > 7) return 0;
        if (reversed < int32_min / 10
            || reversed == int32_min / 10 && cur_digit < -8) return 0;
        
        reversed *= 10;
        reversed += cur_digit;
    }
    return reversed;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter x:\n";
        int x{ };
        cin >> x;
        
        cout << "Here's x with its digits reversed:\n";
        cout << reverse(x) << '\n';
    }
    return 0;
}
