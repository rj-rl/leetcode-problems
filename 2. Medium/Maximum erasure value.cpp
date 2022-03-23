//============================================================================//
//                                                                            //
//          https://leetcode.com/problems/maximum-erasure-value/              //
//                                                                            //
//============================================================================//

#include <iostream>
#include <vector>

using namespace std;


int maximumUniqueSubarray(const vector<int>& nums)
{
    constexpr size_t MAX_NUM_LEN = 10e5; // assignment condition
    vector<int> prev_idx(MAX_NUM_LEN, -1);
    int left {0}, right {0};
    int sum {0};
    int max {0};
    size_t n {nums.size()};

    while (right < n) {
        sum += nums[right];
        for (int prev_occurrence = prev_idx[nums[right]];
            left <= prev_occurrence;
            ++left
            ) {
            sum -= nums[left];
            prev_idx[nums[left]] = -1;
        } // skukojili
        prev_idx[nums[right]] = right;

        max = std::max(max, sum);
        ++right;
    }

    return max;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Input, please!\n";
        vector<int> nums;
        for (int n{ 0 }; cin >> n;) {
            nums.push_back(n);
        }
        cin.clear();
        cin.ignore();
        cout << "The sum of max unique subarray is " << maximumUniqueSubarray(nums) << '\n';
    }
    return 0;
}
