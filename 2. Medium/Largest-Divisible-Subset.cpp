/*
  https://leetcode.com/problems/largest-divisible-subset/

  Given a set of distinct positive integers nums, return its largest subset
  'answer', such that for every pair 'answer[i], answer[j]'
    either 'answer[i] % answer[j]' == 0
    or     'answer[j] % answer[i]' == 0
  If there are multiple solutions, return any of them
/**/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums)
{
    // we sort the array so that we can conventiently check
    // divisibility against the largest member of its pairwise
    // divisible without having to search for it first
    sort(begin(nums), end(nums));

    // contains the minimal info about a set of pairwise divisible (PD)
    // numbers to be able to reconstruct the whole set
    struct SetInfo {
        int prev_id = -1;
        int size = 1;
        bool operator<(SetInfo other)
        {
            return size < other.size;
        }
    };
    // 'memo[i]' contains the size of the PD set
    // for which the max element is 'nums[i]';
    // it also contains the index of the second max element
    vector<SetInfo> memo(nums.size());

    size_t max_idx = 0;
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0) {
                if (memo[i].size < memo[j].size + 1) {
                    memo[i].size = memo[j].size + 1;
                    memo[i].prev_id = j;
                    // remember the idx of max el-t of biggest set
                    if (memo[i].size > memo[max_idx].size) {
                        max_idx = i;
                    }
                }
            }
        }
    }

    vector<int> result;
    for (int i = max_idx; i != -1; i = memo[i].prev_id) {
        result.push_back(nums[i]);
    }
    return result;
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

        auto largest_subset = largestDivisibleSubset(nums);
        cout << "Here's the largest subset of the array, where everything "
            << "divides each other pairwise\n";
        for (auto num : largest_subset) {
            cout << num << ' ';
        }
        cout << '\n';
    }
    return 0;
}
