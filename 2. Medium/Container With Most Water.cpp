//============================================================================//
//                                                                            //
//           https://leetcode.com/problems/container-with-most-water/         //
//                                                                            //
//============================================================================//

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

/*            EXPLANATION

We start with the borders at each end of the array. Which border should move?
Obviously, the limiting factor is the shorter border, so that's the one we move.
Say the left one is shorter and we move it one place to the right, possible scenarios are:

--  if the new left border is <= the old one, the area of water will have decreased,
    since there's now less distance between the borders. We continue moving the left border;

--  if the new left border is > the old one, the area MAY have increased, depending
    on how much bigger the new left border is. Therefore, we need to calc the new area
    and update the historical 'max_area'. Another possibility is that the new left border
    is now > than the right border, at which point we start moving that one.
    If the new left border = right border, we can actually move both simultaneously,
    it won't hurt, since we'd be looking for TWO new borders each taller than the old ones,
    otherwise the area wouldn't increase.
*/
int maxArea(vector<int>& height)
{
    int max_area{ 0 };
    int l = 0, r = height.size() - 1;

    while (l < r) {
        int height_to_beat = std::min(height[l], height[r]);
        max_area = std::max(max_area, (r - l) * height_to_beat);
        while (height[l] <= height_to_beat && l < r)
            ++l;
        while (height[r] <= height_to_beat && l < r)
            --r;
    }
    return max_area;
}

int main ()
{
    std::cout << "Input, please!\n";
    vector<int> borders;    
    for (int n{ 0 }; std::cin >> n;) {
        borders.push_back(n);
    }    
    std::cout << maxArea(borders) << '\n';

    return 0;
}
