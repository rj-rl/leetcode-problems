/*
          https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

  There is an integer array 'nums' sorted in non-decreasing order (not necessarily with distinct values).
  Before being passed to your function, 'nums' is rotated at an unknown pivot index 'k' (0 <= k < nums.length)
  such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
  For example, [0,1,2,4,4,4,5,6,6,7] might be rotated
  at pivot index 5        ^
  and become [4,5,6,6,7,0,1,2,4,4].

  Given the array 'nums' after the rotation and an integer 'target', find out if 'num's contain 'target'.
  You must decrease the overall operation steps as much as possible.
*/

#include <iostream>
#include <vector>

using namespace std;

bool search(const vector<int>& nums, int target)
{
    size_t left = 0u;
    size_t right = nums.size() - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (nums[mid] == target) return true;
        if (nums[left] == target) return true;

        // pivot in the left part
        if (nums[left] > nums[mid]) {
            // target in the right part, which is sorted - yay!
            if (nums[mid] <= target && target <= nums[right]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // pivot in the right part
        else if (nums[mid] > nums[right]) {
            // target in the left part, which is sorted - yay!
            if (nums[left] <= target && target <= nums[mid]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        // could not detect presence of pivot
        else {
            ++left;
        }
    }
    return false;
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

        if (search(nums, target)) {
            cout << "The array does contain target!\n";
        }
        else {
            cout << "Target's nowhere to be found!\n";
        }
    }
    return 0;
}