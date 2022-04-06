/*
  https://leetcode.com/problems/3sum-with-multiplicity/

  Given an integer array 'arr', and an integer target', return the number
  of tuples i, j, k such that i < j < k and 'arr[i] + arr[j] + arr[k] == target'

  As the answer can be very large, return it modulo 10^9 + 7.
/**/

#include <iostream>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>

using namespace std;

template <class Predicate>
int find_last(const vector<int>& arr, int left, int right, Predicate func)
{
    while (left < right) {
        int cur = left + (right - left) / 2 + 1;
        if (func(arr[cur])) left = cur;
        else right = cur - 1;
    }

    if (func(arr[right])) return right;
    else return -1;
}

template <class Predicate>
int find_first(const vector<int>& arr, int left, int right, Predicate func)
{
    while (left < right) {
        int cur = left + (right - left) / 2;
        if (func(arr[cur])) right = cur;
        else left = cur + 1;
    }

    if (func(arr[right])) return right;
    else return -1;
}

//============================================================================//

// ugly helper function
long long combination_count(const vector<int>& arr, int left, int mid, int right)
{
    const int big_prime = 1e9 + 7;

    auto r_left = equal_range(begin(arr), end(arr), left);
    int count_left = distance(r_left.first, r_left.second);
    
    auto r_mid = equal_range(begin(arr), end(arr), mid);
    int count_mid = distance(r_mid.first, r_mid.second);
    
    auto r_right = equal_range(begin(arr), end(arr), right);
    int count_right = distance(r_right.first, r_right.second);

    long long result = 0;
    if (left != mid && left != right && mid != right) {
        result = count_mid * count_left;
        result %= big_prime;
        result *= count_right;
        result %= big_prime;
        return result;
    }
    if (left != mid && mid == right) {
        result = (count_mid * (count_mid - 1)) / 2;
        result %= big_prime;
        result *= count_left;
        result %= big_prime;
        return result;
    }
    if (left == mid && mid != right) {
        result = (count_mid * (count_mid - 1)) / 2;
        result %= big_prime;
        result *= count_right;
        result %= big_prime;
        return result;
    }
    if (left == mid && mid == right) {
        result = (count_mid * (count_mid - 1));
        result %= big_prime;
        result *= (count_mid - 2);
        result /= 6;
        result %= big_prime;
        return result;
    }
    else return -1;
}

int threeSumMulti(vector<int>& arr, int target)
{
    const int big_prime = 1e9 + 7;

    sort(begin(arr), end(arr));
    int size = arr.size();
    long long result = 0;

    for (int left = 0; left < size; ++left) {
        // we've already done this case
        if (left > 0 && arr[left] == arr[left - 1]) continue;
        
        int mid = left + 1;
        int right = size - 1;
        int cur_target = target - arr[left];

        while (mid < right) {
            if ( arr[mid] + arr[right] == cur_target ) {
                result += combination_count(arr, arr[left], arr[mid], arr[right]);
                result %= big_prime;

                // skip repeating numbers
                mid = find_first(arr, mid, right,
                    [&](int x) { return x > arr[mid]; }
                );
                if (mid == -1) break;
                
                right = find_last(arr, mid, right,
                    [&](int x) { return x < arr[right]; }
                );
                if (right == -1) break;
            }
            
            else if (arr[mid] + arr[right] > cur_target) {
                right = find_last(arr, mid, right,
                    [&](int x) { return arr[mid] + x <= cur_target; }
                );
                if (right == -1) break;
            }
            
            else if (arr[mid] + arr[right] < cur_target) {
                mid = find_first(arr, mid, right,
                    [&](int x) { return x + arr[right] >= cur_target; }
                );
                if (mid == -1) break;
            }
        }
    }
    return result;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter the array size:\n";
        int n{ };
        cin >> n;

        cout << "Enter the array:\n";
        vector<int> arr;
        while (n-- > 0) {
            int x{ };
            cin >> x;
            arr.push_back(x);
        }

        cout << "Enter the target:\n";
        int target {};
        cin >> target;

        cout << "The number of triplets i, j, k: arr[i] + arr[j] + arr[k]"
            << " == target is (modulo 10 ^ 9 + 7)\n"
            << threeSumMulti(arr, target) << '\n';
    }
    return 0;
}
