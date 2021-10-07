//==============================================================================================//
//                                                                                              //
//			https://leetcode.com/problems/two-sum/					//
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

vector<int> twoSum(vector<int>& nums, int target) 
{
	unordered_map<int, int> table;
	for( int i {0}; i < nums.size(); ++i) {
		table[nums[i]] = i;
	}
        
	for( int i {0}; i < nums.size(); ++i) {
		int counterpart = target - nums[i];
		auto it = table.find(counterpart);
		if( it != table.end() && it->second != i ) {
			return {i, it->second};
		}
	}
	return {-1, -1};
}

//================================================================================================
//================================================================================================

int main()
{
	// TEST maximumUniqueSubarray here

	return 0;
}