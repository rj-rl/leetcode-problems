/*
  https://leetcode.com/problems/shift-2d-grid/

  Given a 2D matrix of size 'm x n' and an integer 'k', right-shift the matrix 'k' times
/**/

#include <iostream>
#include <vector>

using namespace std;

// returns reference to the nth element, counting naturally
// left-to-right and top-to-bottom
int& get_nth(vector<vector<int>>& vec, int n)
{
    int num_rows = vec.size();
    int num_cols = vec[0].size();
    return vec[(n / num_cols) % num_rows][n % num_cols];
}

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k)
{
    int num_rows = grid.size();
    int num_cols = grid[0].size();
    int num_els = num_rows * num_cols;

    k = k % num_els;         // don't want to cycle the entire grid multiple times
    if (k == 0) return grid;  // don't want to do useless work

    vector<vector<int>> result(num_rows, vector<int>(num_cols));
    int dest = 0;
    int source = num_els - k;
    do {
        get_nth(result, dest) = get_nth(grid, source);
        dest = (dest + 1) % num_els;
        source = (source + 1) % num_els;
    } while (dest != 0);  // this condition means we've wrapped around

    return result;
}

//==============================================================================================//

int main()
{
    while (true) {
        cout << "Enter the number of rows:\n";
        int m{ };
        cin >> m;

        cout << "Enter the number of columns:\n";
        int n{ };
        cin >> n;

        cout << "Enter the matrix!\n";
        vector<vector<int>> matrix;
        while (m-- > 0) {
            vector<int> row;
            for (int i = 0; i < n; ++i) {
                int x{ };
                cin >> x;
                row.push_back(x);
            }
            matrix.push_back(move(row));
        }

        cout << "How far are we shifting the thing?\n";
        int k{ };
        cin >> k;

        auto shifted = shiftGrid(matrix, k);
        cout << "Here you go:\n";
        for (auto& row : shifted) {
            for (int el : row) {
                cout << el << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}
