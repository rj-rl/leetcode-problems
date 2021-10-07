//==============================================================================================//
//                                                                                              //
//						https://leetcode.com/problems/maximum-subarray/							//
//  Given an integer array nums, find the contiguous subarray (containing at least one number)  //
//	which has the largest sum and return its sum												//
//                                                                                              //
//==============================================================================================//

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

//================================================================================================

int maxSubArray(vector<int>& nums)
{
	int l = 0, r = -1, n = nums.size();
	int max_sum = std::numeric_limits<int>::min();
	int running_sum = 0;
	while (r < n - 1) {
		++r;
		running_sum += nums[r];
		max_sum = std::max(max_sum, running_sum);
		if (running_sum < 0) {
			l = r;
			running_sum = 0;
		}
	}
	return max_sum;
}

//================================================================================================

int main()
{
	while (true) {
		vector<int> v;
		cout << "enter vector:\n";
		int n;
		while (cin >> n) {
			v.push_back(n);
		}
		cin.clear();

		cout << "\ntest result: "
			<< maxSubArray(v)
			<< '\n';
	}
	return 0;
}
