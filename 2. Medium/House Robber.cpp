/*
  https://leetcode.com/problems/house-robber/

  You are a professional robber planning to rob houses along a street.
  Each house has a certain amount of money stashed, the only constraint stopping you
  from robbing each of them is that adjacent houses have security systems connected
  and it will automatically contact the police if two adjacent houses were broken into on the same night.

  Given an integer array 'nums' representing the amount of money of each house,
  return the maximum amount of money you can rob tonight without alerting the police
/**/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ask_known(const vector<int>& subsolutions, int i)
{
    int n = subsolutions.size();
    return i < n ? subsolutions[i] : 0;
}

int rob(const vector<int>& nums)
{
    if (nums.empty()) return -1;

    int n = nums.size();
    // 'subsolutions[i]' contains solution to subproblem
    // for the range ['nums[i]', 'nums[n-1]']
    vector<int> subsolutions(n);
    subsolutions[n - 1] = nums[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        subsolutions[i] = max(
            nums[i]     + ask_known(subsolutions, i + 2),
            nums[i + 1] + ask_known(subsolutions, i + 3)
        );
    }
    return subsolutions[0];
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n{ };
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x{ };
            cin >> x;
            nums.push_back(x);
        }

        cout << "Max loot value is\n" << rob(nums) << '\n';
    }
    return 0;
}
