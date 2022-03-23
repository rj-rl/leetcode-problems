/*
          https://leetcode.com/problems/minimize-deviation-in-array/

    You are given an array 'nums' of 'n' positive integers.
    Two types of operations can be performed on any element any number of times:

    If the element is even, it can be divided by 2
      For example, if the array is [1,2,3,4], you can modify the last element and get [1,2,3,2];
    If the element is odd, it can be multiplied by 2
      For example, if the array is [1,2,3,4], you can modify the first element and get [2,2,3,4].

    The deviation of the array is the maximum difference between any two elements in the array.
    Return the minimum deviation the array can have after performing some number of operations
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int minimumDeviation(const vector<int>& nums)
{
    int min_distance{ 1'000'000'000 };
    int min{ 1'000'000'000 };
    priority_queue<int> queue;
    
    for (auto x : nums) {   // get rid of all odd nums for uniformity
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
        min_distance = std::min(min_distance, abs(x - min));
    }
    return min_distance;
}

//================================================================================================

int main()
{
    while (true) {
        cout << "Enter the array:\n";
        vector<int> v;
        int n;
        while (cin >> n) {
            v.push_back(n);
        }
        cin.clear();
        cin.ignore();
        cout << "Minimum deviation after tweaking:\n"
            << minimumDeviation(v) << '\n';
    }
    return 0;
}
