/*
  https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix
/**/

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> kWeakestRows(const vector<vector<int>>& mat, int k)
{
    set<pair<int, int>> ordering;
    for (int i = 0; i < mat.size(); ++i) {
        auto& row = mat[i];
        auto zero_it = upper_bound(begin(row),
                                  end(row),
                                  1,
                                  greater<int>{});
        int power = distance(begin(row), zero_it);
        ordering.emplace(power, i);
    }

    vector<int> result;
    for (auto it = begin(ordering);
        it != end(ordering) && k > 0;
        --k, ++it) {
        result.push_back(it->second);
    }
    return result;
}
//============================================================================//

int main()
{
    while (true) {
        cout << "Enter number of rows:\n";
        int n{};
        cin >> n;
        vector<vector<int>> matrix(n);
        cin.ignore();

        cout << "Matrix elements, please:\n";
        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            istringstream ss{ line };
            
            matrix[i] = vector<int>{ istream_iterator<int> { ss }, istream_iterator<int> { } };
        }

        cout << "Enter k:\n";
        int k{};
        cin >> k;

        auto result = kWeakestRows(matrix, k);
        cout << "Here's the indices of k weakest rows:\n";
        for (auto idx : result) {
            cout << idx << ' ';
        }
        cout << '\n';
    }
    return 0;
}
