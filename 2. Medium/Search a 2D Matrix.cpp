/*
          https://leetcode.com/problems/search-a-2d-matrix/

  Write an efficient algorithm that searches for a value 'target' in an m x n integer matrix 'matrix'.
  This matrix has the following properties:
    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// return nth element of the 'matrix', counting left-to-right and top-to-bottom
int get_nth_elem(const vector<vector<int>>& matrix, int n)
{
    int row_idx = n / matrix[0].size();
    int col_idx = n % matrix[0].size();
    return matrix[row_idx][col_idx];
}

bool searchMatrix(const vector<vector<int>>& matrix, int target)
{
    if (matrix.empty()) return false;
    if (matrix[0].empty()) return false;

    int left = 0u;
    int right = matrix.size() * matrix[0].size() - 1;

    while (left <= right) {
        int cur = left + (right - left) / 2;
        int cur_elem = get_nth_elem(matrix, cur);
        
        if (cur_elem == target) return true;
        if (cur_elem < target) left = cur + 1;
        if (cur_elem > target) right = cur - 1;
    }
    return false;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter the number of rows:\n";
        int m{ };
        cin >> m;

        cout << "Enter the number of columns:\n";
        int n{ };
        cin >> n;

        cout << "Enter the target:\n";
        int target{ };
        cin >> target;

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
        
        if (searchMatrix(matrix, target))
            cout << "Search successful!\n";
        else
            cout << "Target's nowhere to be found!\n";
    }
    return 0;
}
