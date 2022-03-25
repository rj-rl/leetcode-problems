/*
          https://leetcode.com/problems/two-city-scheduling/

  A company is planning to interview '2n' people. Given the array costs where 'costs[i] = [aCost_i, bCost_i]',
  the cost of flying the ith person to city a is 'aCost_i', and the cost of flying the ith person to city b is 'bCost_i'.

  Return the minimum cost to fly every person to a city such that exactly 'n' people arrive in each city.
*/

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

int twoCitySchedCost(vector<vector<int>>& costs)
{
    sort(begin(costs), end(costs),
         [](const vector<int>& l, const vector<int>& r) {
             return l[0] - l[1] < r[0] - r[1];
         });
    int min_cost = 0;
    size_t n = costs.size();
    min_cost += accumulate(begin(costs), begin(costs) + n / 2, 0,
                           [](int total, const vector<int>& el) {
                               return total + el[0];
                           });
    min_cost += accumulate(begin(costs) + n / 2, end(costs), 0,
                           [](int total, const vector<int>& el) {
                               return total + el[1];
                           });
    return min_cost;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter number of people\n";
        int n;
        cin >> n;

        cout << "Enter vector of costs (pairs of positive numbers)\n";
        vector<vector<int>> costs(n);
        for (size_t i = 0u; i < n; ++i) {
            int cost_A_i;
            int cost_B_i;
            cin >> cost_A_i >> cost_B_i;
            costs[i].push_back(cost_A_i);
            costs[i].push_back(cost_B_i);
        }
        cout << "Minimum cost to fly everyone such that half the guys end up in A and another half in B is:\n";
        cout << twoCitySchedCost(costs) << '\n';
    }
    return 0;
}