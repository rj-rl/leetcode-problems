/*
  https://leetcode.com/problems/path-with-minimum-effort/

  Given the matrix 'heights', which describes terrain height in a grid,
  return minimum cost of the path from top-left to bottom-right,
  where a path's cost is the maximum absolute difference in heights between
  two consecutive cells of the path
/**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cassert>
#include <limits>

using namespace std;

struct CostData {
    int cost = 0;
    int row = 0;
    int col = 0;
};

struct CostDataCmp {
    bool operator()(const CostData& a, const CostData& b) const 
    { 
        return a.cost > b.cost;
    }
};

int minimumEffortPath(const vector<vector<int>>& heights)
{
    int num_rows = heights.size();
    int num_cols = heights[0].size();

    vector<vector<int>> costs(
        num_rows, vector<int>(num_cols, numeric_limits<int>::max())
    );
    vector<int> dir {0, 1, 0, -1, 0};

    priority_queue<CostData, vector<CostData>, CostDataCmp> pq;
    costs[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [cost, i, j] = pq.top();
        pq.pop();
        
        if (i == num_rows - 1 && j == num_cols - 1)
            break;

        if (cost >= costs[i][j]) continue;

        for (auto d = 0; d < 4; ++d) {
            int x = i + dir[d], y = j + dir[d + 1];
            if (x >= 0 && y >= 0 && x < num_rows && y < num_cols) {
                int updated_cost = max(
                    costs[i][j], abs(heights[i][j] - heights[x][y])
                );
                if (updated_cost < costs[x][y]) {
                    costs[x][y] = updated_cost;
                    pq.push({updated_cost, x, y});
                }
            }
        }
    }
    return costs[num_rows - 1][num_cols - 1];
}

//==============================================================================================//

int main()
{
    while (true) {
    // TODO: ask for input, present the output
    }
    return 0;
}
