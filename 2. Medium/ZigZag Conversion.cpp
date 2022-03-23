//============================================================================//
//                                                                            //
//             https://leetcode.com/problems/zigzag-conversion/               //
//                                                                            //
//============================================================================//

#include <iostream>
#include <string>

using namespace std;

// Returns the next index in a string following zigzag pattern DOWNWARDS
// Assumes num_rows > 1
int nextIdx(int cur_idx, int num_rows)
{
    return cur_idx + (num_rows - 1) * 2;
}

string convert(string s, int numRows)
{
    if (numRows == 1) return s;
    
    string res;
    int n = s.length();
    
    for (int cur_lvl = 0; cur_lvl < numRows; ++cur_lvl) {
        bool is_going_down{ true };
        if (cur_lvl == numRows - 1) {
            is_going_down = false; // always go up from the last lvl
        } 
        for (int cur_idx{ cur_lvl }; cur_idx < n;) {
            res += s[cur_idx];
            cur_idx = is_going_down
                ? nextIdx(cur_idx, numRows - cur_lvl)
                : nextIdx(cur_idx, cur_lvl + 1);
            if (0 < cur_lvl && cur_lvl < numRows - 1) {
                is_going_down = !is_going_down;
            }
        }
    }
    return res;
}

//============================================================================//

int main ()
{
    string input;
    int n{ 1 };
    cout << "Please enter string and numRows:\n";
    cin >> input >> n;
    cout << convert(input, n);

    return 0;
}
