/*
  https://leetcode.com/problems/longest-increasing-subsequence/

  Given an integer array 'nums', return the length
  of the longest strictly increasing subsequence.

  A subsequence is a sequence that can be derived from an array
  by deleting some or no elements without changing the order
  of the remaining elements.
  For example [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7]
/**/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lengthOfLIS(const vector<int>& nums)
{
    auto size = nums.size();
    if (size == 0) return 0;
    // 'longest[i]' contains longest increasing subsequence
    // in 'nums[0, i]' which ENDS on 'i'th element
    // meaning the longest sequence overall is not necessarily
    // 'longest[size - 1]' since it might've ended on a previous el-t
    vector<int> longest(size, 1);

    for (size_t i = 1; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                longest[i] = max(longest[i], 1 + longest[j]);
            }
        }
    }
    return *max_element(begin(longest), end(longest));
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter the array (any letter to stop):\n";
        vector<int> nums;
        int x{};
        while (cin >> x) {
            nums.push_back(x);
        }
        cin.clear();
        cin.ignore();

        cout << "Length of longest increasing subsequence is "
            << lengthOfLIS(nums) << '\n';
    }
    return 0;
}
