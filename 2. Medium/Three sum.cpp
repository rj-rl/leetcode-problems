/*
          https://leetcode.com/problems/3sum/

    Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
    such that i, j and k are different, and nums[i] + nums[j] + nums[k] == 0.

    The solution set must not contain duplicate triplets.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums)
{
    if (nums.size() <= 1) return {};
    
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;

    for (size_t i{ 0 }; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // skip repeats
        
        size_t left = i + 1;
        size_t right = nums.size() - 1;        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({ nums[i], nums[left], nums[right] });
                do ++left;
                    while (left < right && nums[left] == nums[left - 1]);
                do --right;
                    while (left < right && nums[right] == nums[right + 1]);
            }
            else {
                if (sum > 0) {
                    do --right;
                        while (left < right && nums[right] == nums[right + 1]);
                }
                else {
                    do ++left;
                        while (left < right && nums[left] == nums[left - 1]);
                }
            }
        }
    }
    
    return result;
}

//============================================================================//

int main ()
{
    while (true) {
        cout << "Input, please! Length followed by elements:\n";
        
        vector<int> nums;
        int n{ 0 };
        
        cin >> n;
        while (n--) {
            int x;
            cin >> x;
            nums.push_back(x);
        }
        
        for (const auto& index_set : threeSum(nums)) {
            cout << "[ ";
            for (auto x : index_set) {
                cout << x  << ' ';
            }
            cout << "]\n";
        }
    }
    return 0;
}
