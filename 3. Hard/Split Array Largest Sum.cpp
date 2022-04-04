/*
  https://leetcode.com/problems/split-array-largest-sum/

  Given an array 'nums' which consists of non-negative integers and an integer 'm',
  the array can be split into 'm' non-empty continuous subarrays.
  Write an algorithm to minimize the largest sum among these 'm' subarrays.
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// returns true if 'nums' can be split into 'bucket_count' continuous subarrays
// such that each sums to 'max' or less
bool is_splittable(const vector<int>& nums, int bucket_count, int max)
{
    int size = nums.size();
    int i = 0;
    while (bucket_count-- > 0) {
        int bucket_sum = 0;
        while (bucket_sum <= max) {
            if (i == size) return true;
            bucket_sum += nums[i];
            ++i;
        }
        --i;
    }
    return false;
}

int splitArray(const vector<int>& nums, int bucket_count)
{
    int size = nums.size();
    if (size == 0 || size < bucket_count) return 0;

    int max_el = *max_element(begin(nums), end(nums));
    int left   = max_el;
    int right  = max_el * (size / bucket_count + 1);  // rough estimate, +1 instead of ceil
    
    while (left < right) {
        int cur = left + (right - left) / 2;
        if (is_splittable(nums, bucket_count, cur)) right = cur;
        else left = cur + 1;
    }
    return left;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n = 0;
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x = 0;
            cin >> x;
            nums.push_back(x);
        }

        cout << "Enter the number of buckets m:\n";
        int bucket_count = 0;
        cin >> bucket_count;

        cout << "Minimal largest sum of el-s in a bucket is:\n";
        cout << splitArray(nums, bucket_count) << '\n';
    }
    return 0;
}
