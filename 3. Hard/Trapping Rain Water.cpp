/*
  https://leetcode.com/problems/trapping-rain-water/

  Given 'n' non-negative integers representing an elevation map
  where the width of each bar is 1, compute how much water it can trap after raining
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int trap(const vector<int>& height)
{
    int left = 0;
    int right = height.size() - 1;
    int previous_water_lvl = 0;
    int submerged_area = 0;
    int submerged_wall_area = 0;

    while (left < right) {
        int water_lvl = min(height[left], height[right]);
        // a wall section is considered submerged 
        // if there's water to the left/right of it
        submerged_area += (right - left + 1) * (water_lvl - previous_water_lvl);
        previous_water_lvl = water_lvl;

        while (height[left] <= water_lvl && left < right) {
            submerged_wall_area += height[left];
            ++left;
        }
        while (height[right] <= water_lvl && left < right) {
            submerged_wall_area += height[right];
            --right;
        }
    }
    // this is submerged part of the tallest wall;
    // we leave the main loop just as we reach it, so add it now
    submerged_wall_area += previous_water_lvl;

    return submerged_area - submerged_wall_area;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n{ };
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> nums;
        while (n-- > 0) {
            int x{ };
            cin >> x;
            nums.push_back(x);
        }

        cout << "The amount of water trapped is\n" << trap(nums) << '\n';
    }
    return 0;
}
