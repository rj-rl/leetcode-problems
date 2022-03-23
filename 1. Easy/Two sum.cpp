//============================================================================//
//                                                                            //
//               https://leetcode.com/problems/two-sum/                       //
//                                                                            //
//============================================================================//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twoSum(const vector<int>& nums, int target) 
{
	unordered_map<int, int> table;
	
	for( int i {0}; i < nums.size(); ++i) {
		int counterpart = target - nums[i];
		auto it = table.find(counterpart);
		if( it != table.end()) {
			return {it->second, i};
		}		
		table[nums[i]] = i;
	}
	return {-1, -1};
}

//============================================================================//

int main()
{
	while (true) {
		cout << "enter vector length:\n";
		int n {};
		cin >> n;
		vector<int> nums;
		nums.reserve(n);

		cout << "vector elements please:\n";
		while (n--) {
			int x {};
			cin >> x;
			nums.push_back(x);
		}

		cout << "what's our target?\n";
		int target {};
		cin >> target;

		auto result = twoSum(nums, target);
		if( result[0] == -1) {
			cout << "can't reach the target, tough luck mate!\n";
			continue;
		}
		cout << "elements with these indices add up to target:\n";
		for( auto el : result) {
			cout << el << ' ';
		}
		cout << '\n';
	}
	return 0;
}

