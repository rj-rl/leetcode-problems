//============================================================================//
//                                                                            //
//             https://leetcode.com/problems/integer-to-roman/                //
//                                                                            //
//============================================================================//

#include <iostream>
#include <string>
#include <sstream>
using std::string;

string digitToRomanTriplets(int digit, char high, char mid, char low)
{
    std::ostringstream roman;
    if (digit == 9) {
        roman << low << high;
    }
    else if (5 <= digit) {
        roman << mid;
        while (digit > 5) {
            roman << low;
            --digit;
        }
    }
    else if (digit == 4) {
        roman << low << mid;
    }
    else {
        while (digit) {
            roman << low;
            --digit;
        }
    }
    return roman.str();
}

string intToRoman(int num)
{
    string roman;

    int thousands = num / 1000;
    num -= thousands * 1000;
    int hundreds = num / 100;
    num -= hundreds * 100;
    int tens = num / 10;
    num -= tens * 10;
    int ones = num;

    while (thousands--) {
        roman += 'M';
    }
    roman += digitToRomanTriplets(hundreds, 'M', 'D', 'C');
    roman += digitToRomanTriplets(tens, 'C', 'L', 'X');
    roman += digitToRomanTriplets(ones, 'X', 'V', 'I');

    return roman;
}

int main ()
{
    string s;
    while (true) {
        std::cout << "Input, please!\n";
        int n;
        std::cin >> n;
        std::cout << intToRoman(n) << '\n';
    }    
    return 0;
}
