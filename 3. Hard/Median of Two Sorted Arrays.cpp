/*
          https://leetcode.com/problems/median-of-two-sorted-arrays/

    Given two sorted arrays 'nums1' and 'nums2' of size 'm' and 'n' respectively,
    return the median of the two sorted arrays.

    The overall run time complexity should be O(log(m+n))

    SEE DETAILED EXPLANATION OF THE SOLUTION HERE: https://youtu.be/LPFhl65R7ww
*/

#include <iostream>
#include <vector>
#include <limits>
using std::vector;

double median(const vector<int>& nums)
{
    return nums.size() % 2
        ? nums[nums.size() / 2]
        : (nums[nums.size() / 2] + nums[nums.size() / 2 - 1]) / 2.0;
}

// helper functions to get elements left and right of the cut position
// return infinities for correct comparisons if out of bounds
int leftElem(const vector<int>& nums, size_t i)
{
    if (i == 0) return std::numeric_limits<int>::min();
    return nums[i - 1];
}

int rightElem(const vector<int>& nums, size_t i)
{
    if (i == nums.size()) return std::numeric_limits<int>::max();
    return nums[i];
}

double findMedianSortedArrays(vector<int>& big, vector<int>& small)
{
    size_t n_big  { big.size() },
           n_small{ small.size() };
    
    if (n_big < n_small)
        return findMedianSortedArrays(small, big);  // makes sure 'big' really is big

    size_t half{ (n_big + n_small + 1) / 2 };   // half the elements (rounded up if odd)
    size_t from{ 0u }, to{ n_small };  // the window (2 cut positions) in the smaller array within which we search
    size_t cut_small{ (from + to) / 2 }, 
           cut_big{ half - cut_small };
    
    while (true) {
        cut_small = (from + to) / 2;
        cut_big = half - cut_small;
        
        if (leftElem(small, cut_small) <= rightElem(big, cut_big)
            && leftElem(big, cut_big) <= rightElem(small, cut_small)) {
            return (n_big + n_small) % 2
                ? std::max(leftElem(small, cut_small), leftElem(big, cut_big))
                : (std::max(leftElem(small, cut_small), leftElem(big, cut_big))
                    + std::min(rightElem(small, cut_small), rightElem(big, cut_big))) / 2.0;
        }
        else if (leftElem(big, cut_big) > rightElem(small, cut_small)) {
            from = cut_small + 1;
        }
        else {  // leftElem in smaller array is too big, move cut_small to the left
            to = cut_small - 1;
        }
    }
}

int main ()
{
    while (true) {
        std::cout << "Input, please! Length followed by elements, for both vectors\n";
        vector<int> v1, v2;
        int n1{ 0 }, n2{ 0 };
        std::cin >> n1;
        while (n1--) {
            int x;
            std::cin >> x;
            v1.push_back(x);
        }
        std::cout << "and now the second\n";
        std::cin >> n2;
        while (n2--) {
            int x;
            std::cin >> x;
            v2.push_back(x);
        }
        std::cout << findMedianSortedArrays(v1, v2) << '\n';
    }    
    return 0;
}
