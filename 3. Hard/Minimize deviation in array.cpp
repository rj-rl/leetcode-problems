//==============================================================================================//
//                                                                                              //
//			leetcode.com/problems/minimize-deviation-in-array/				//
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
#include <queue>
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

int minimumDeviation(vector<int>& nums)
{
	int min_distance {1'000'000'000}, min {1'000'000'000};
	std::priority_queue<int> queue;
	for (auto x : nums) {
		x = x % 2 ? x * 2 : x;
		queue.push(x);
		min = std::min(min, x);
	}
	int x = queue.top();
	while (x % 2 == 0) {
		queue.pop();
		queue.push(x / 2);
		min = std::min(min, x / 2);
		x = queue.top();
		min_distance = std::min(min_distance, std::abs(x - min));
	}
	return min_distance;
}

//================================================================================================

int main()
{
	cout << "enter the array:\n";
	std::vector<int> v;
	int n;
	while (cin >> n) {
		v.push_back(n);
	}
	cout << "test result:\n"
		<< minimumDeviation(v);	

	return 0;
}