/*
          https://leetcode.com/problems/search-in-rotated-sorted-array/

  There is an integer array 'nums' sorted in non-decreasing order (with distinct values).
  Before being passed to your function, 'nums' is rotated at an unknown pivot index 'k' (0 <= k < nums.length)
  such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
  For example, [0,1,2,4,4,4,5,6,6,7] might be rotated
  at pivot index 5        ^
  and become [4,5,6,6,7,0,1,2,4,4].

  Given the array 'nums' after the possible rotation and an integer 'target',
  return the index of 'target' if it is in 'nums', or -1 if it is not in 'nums'.
  You must write an algorithm with O(log n) runtime complexity.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// retuns index of the pivot;
// rotating left at this pivot will result in the vector being sorted
size_t find_pivot(const vector<int>& nums)
{
    size_t left = 0u;
    size_t right = nums.size() - 1;

    // 'nums' is already sorted, meaning 'pivot == 0'
    if (nums[left] <= nums[right]) return 0u;

    while (left < right - 1) {
        size_t mid = left + (right - left) / 2;
        if (nums[mid] < nums[left]) right = mid;
        else if (nums[mid] > nums[right]) left = mid;
    }
    return right;
}

int search(const vector<int>& nums, int target)
{
    size_t pivot = find_pivot(nums);
    auto pivot_it = next(begin(nums), pivot);

    auto find_in_left = lower_bound(begin(nums), pivot_it, target);
    if (find_in_left != pivot_it && *find_in_left == target)
        return distance(begin(nums), find_in_left);

    auto find_in_right = lower_bound(pivot_it, end(nums), target);
    if (find_in_right != end(nums) && *find_in_right == target)
        return distance(begin(nums), find_in_right);

    return -1;
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

        cout << "Enter target:\n";
        int target{ };
        cin >> target;

        int pos = search(nums, target);
        if (pos != -1) {
            cout << "Target found at position " << pos << '\n';
        }
        else {
            cout << "Target nowhere to be found!\n";
        }
    }
    return 0;
}
