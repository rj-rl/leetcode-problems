//============================================================================//
//                                                                            //
//          https://leetcode.com/problems/maximum-subarray/                   //
//  Given an integer array nums, find the contiguous subarray                 //
//  (containing at least one number) which has the largest sum                //
//  and return its sum                                                        //
//                                                                            //
//============================================================================//

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int maxSubArray(const vector<int>& nums)
{
    int r = 0;
    int n = nums.size();
    int max_sum = numeric_limits<int>::min();
    int running_sum = 0;
    while (r < n) {
        running_sum += nums[r];
        max_sum = max(max_sum, running_sum);
        if (running_sum < 0) {
            running_sum = 0;
        }
        ++r;
    }
    return max_sum;
}

//============================================================================//

int main()
{
    while (true) {
        vector<int> v;
        cout << "Enter vector:\n";
        int n;
        while (cin >> n) {
            v.push_back(n);
        }
        cin.clear();

        cout << "\nTest result: "
            << maxSubArray(v)
            << '\n';
    }
    return 0;
}
