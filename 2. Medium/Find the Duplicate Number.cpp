/*
          https://leetcode.com/problems/find-the-duplicate-number/

  An array of integers 'nums' contains n + 1 integers where each integer is in the range [1, n] inclusive.
  There is only one repeated number in 'nums', return this repeated number.
  
  You must solve the problem without modifying the array nums and uses only constant extra space.
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// returns the number of el-s in 'nums' which are <= 'target'
int count_leq_nums(const vector<int>& nums, int target)
{
    int count{ 0 };
    for (auto el : nums) {
        if (el <= target) ++count;
    }
    return count;
}

// Note that in an array of integers [1,n], where each number is encountered once
// the count of any number i is precisely i. Since any given number could be replaced
// by the perpetrator (the duplicate), the count of i in 'nums' should be <= i.
// The only way it could be > i is if i > dup. Hence we search for the first
// number i such that count(i) > i.
int findDuplicate(const vector<int>& nums)
{
    if (nums.empty()) return -1;

    size_t left{ 1 };
    // '-1' since el-s <= n while size of 'nums' is n+1
    size_t right{ nums.size() - 1 };

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (count_leq_nums(nums, mid) > mid) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter array size:\n";
        int n{ };
        cin >> n;

        cout << "Enter array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x{ };
            cin >> x;
            nums.push_back(x);
        }

        cout << "The repeating number is " << findDuplicate(nums) << '\n';
    }
    return 0;
}