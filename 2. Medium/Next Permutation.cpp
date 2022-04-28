/*
  https://leetcode.com/problems/next-permutation

  Given an array of integers 'nums', find the next permutation of 'nums'.
  The replacement must be in place and use only constant extra memory
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

// What we essentially are trying to do is to find the rightmost pair of idxs 'left', 'right'
// such that switching those el-s makes 'nums' lexico bigger by making 'nums[left]' bigger.
// Example: 5 (3) 7 (4) 2 -> 5 (4) 7 (3) 2
// But if we simply switch, 'nums' could easily skip a few permutations, for example
// we missed this one: 5 4 2 3 7 or this one: 5 4 3 2 7;
// This is why we sort 'nums' from position 'left + 1' onwards
// (remember, sorting in increasing order gives you lexico smallest sequence)
void nextPermutation(vector<int>& nums)
{
    if (nums.empty()) return;

    int n = nums.size();
    int rightmost_lesser = 0;
    int max_seen = numeric_limits<int>::min();

    for (int i = n - 1; i >= 0; --i) {
        if (nums[i] > max_seen) {
            max_seen = nums[i];
            continue;
        }
        if (nums[i] < max_seen) {
            rightmost_lesser = i;
            break;
        }
    }

    int rightmost_bigger = 0;
    for (int i = n - 1; i > rightmost_lesser; --i) {
        if (nums[rightmost_lesser] < nums[i]) {
            rightmost_bigger = i;
            break;
        }
    }
    // the array was sorted in decreasing order;
    // next permutation by definition then is the array sorted in increasing order
    if (rightmost_bigger == 0) {
        reverse(begin(nums), end(nums));
        return;
    }

    swap(nums[rightmost_lesser], nums[rightmost_bigger]);
    sort(next(begin(nums), rightmost_lesser + 1), end(nums));
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n {};
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x { };
            cin >> x;
            nums.push_back(x);
        }

        nextPermutation(nums);
        cout << "Here's the next permutation\n";
        for (auto num : nums) {
            cout << num << ' ';
        }
        cout << '\n';

        while (true) {
            cout << "Want some more permutations of the same array? (y/n)\n";
            char answer = 'n';
            cin >> answer;
            if (answer != 'y') break;

            nextPermutation(nums);
            cout << "Here's the next permutation\n";
            for (auto num : nums) {
                cout << num << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
