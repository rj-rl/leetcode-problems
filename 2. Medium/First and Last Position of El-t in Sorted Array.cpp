/*
  https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

  Given an array of integers 'nums' sorted in non-decreasing order,
  find the starting and ending position of a given 'target' value.
  If 'target' is not found in the array, return [-1, -1].

  You must write an algorithm with O(log n) runtime complexity.
/**/

#include <iostream>
#include <vector>

using namespace std;

// returns position of first el-t in 'nums' not less than 'target', -1 if not found
// 'nums' must be sorted in non-decreasing order
int lower_bound(const vector<int>& nums, int target)
{
    int sz = nums.size();
    if (sz == 0) return -1;
    
    int left = 0;
    int right = sz - 1;

    while (left < right) {
        int cur = left + (right - left) / 2;
        if (nums[cur] < target) left = cur + 1;
        if (nums[cur] >= target) right = cur;
    }

    if (nums[right] >= target) return right;
    else return -1;
}

vector<int> searchRange(const vector<int>& nums, int target)
{
    int first = lower_bound(nums, target);
    int last = lower_bound(nums, target + 1);
    
    if (first == -1 || first == last)
        return { -1, -1 };
    // means 'nums' ends with 1 or more copies of 'target'
    else if (last == -1)
        return { first, static_cast<int>(nums.size()) - 1 };
    else
        return { first, last - 1 };
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

        cout << "Enter target:\n";
        int target{ };
        cin >> target;

        auto range = searchRange(nums, target);
        if (range[0] == -1) {
            cout << "Target's nowhere to be found!\n";
        }
        else {
            cout << "Target found from " << range[0]
                << " to " << range[1] << '\n';
        }
    }
    return 0;
}
