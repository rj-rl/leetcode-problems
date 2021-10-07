//==============================================================================================//
//                                                                                              //
//			https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero				//
//                                                                                              //
//==============================================================================================//

#include "test_runner.h"
#include "profile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <queue>
#include <numeric>
#include <functional>
#include <iomanip>
#include <limits>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <stdexcept>
#include <bitset>
#include <random>

using namespace std;

//================================================================================================

/*
	The problem is equivalent to finding the longest subarray
	that sums to 'total - x', where 'total' is the sum of all el-s in 'nums'
	Denote 'sum' the sum of elements within the sliding window

	Algorithm:
	1. Grow the window by shifting right edge ('e' for end) if 'sum < total - x'
	2. While 'sum > total - x', shrink by shifting left edge ('b' for begin)
	3. Check if 'sum == total - x'
		if yes, remember the positions of the edges and shrink the window
		(could shift the whole window, but it requires an additional check for 'e < n')
	4. Start over from 1.

	Loop invariant: the right edge is exclusive, the window is [b, e)

	Stop conditions: 
	- right edge is past the end
	- 'b > e' (happens iff 'total <= x')
*/

int minOperations(vector<int>& nums, int x)
{
	int total = std::accumulate(nums.begin(), nums.end(), 0);
	int n = nums.size();
	int b = 0, e = 0;
	int sum = 0;
	int max_size = -1;

	while (b <= e && e < n) {
		if (sum < total - x) {
			sum += nums[e];
			++e;
		}
		while (sum > total - x) {
			sum -= nums[b];
			++b;
		}
		if (sum == total - x) {
			max_size = std::max(max_size, e - b);
			sum -= nums[b];
			++b;
		}
	}
	return max_size >= 0 ? (n - max_size) : -1;
}

//================================================================================================

int main()
{
	while (true) {
		int x;
		cout << "enter x: ";
		cin >> x;
		vector<int> v;
		cout << "enter vector:\n";
		int n;
		while (cin >> n) {
			v.push_back(n);
		}
		cin.clear();

		cout << "\ntest result: "
			<< minOperations(v, x)
			<< '\n';
	}
	return 0;
}