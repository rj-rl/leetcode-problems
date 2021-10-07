//==============================================================================================//
//                                                                                              //
//		https://leetcode.com/problems/maximum-erasure-value/				//
//                                                                                              //
//==============================================================================================//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <stdexcept>
#include <bitset>
#include <random>

using namespace std;

//================================================================================================

int maximumUniqueSubarray(vector<int>& nums)
{
	constexpr size_t MAX_NUM_LEN = 10e5; // from assignment conditions
    vector<int> prev_idx(MAX_NUM_LEN, -1);
    int left {0}, right {0};
    int sum {0};
    int max {0};
    size_t n {nums.size()};

    while (right < n) {
        sum += nums[right];
        for (int prev_occurrence = prev_idx[nums[right]]; left <= prev_occurrence; ++left) {
            sum -= nums[left];
            prev_idx[nums[left]] = -1;
        } // skukojili
        prev_idx[nums[right]] = right;

        max = std::max(max, sum);
        ++right;
    }

    return max;
}

//================================================================================================
//================================================================================================

int main()
{
	// TEST maximumUniqueSubarray here

	return 0;
}
