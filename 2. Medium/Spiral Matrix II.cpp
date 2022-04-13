/*
  https://leetcode.com/problems/spiral-matrix-ii/

  Given a positive integer 'n', generate an 'n x n' matrix filled
  with elements 1, 2, 3, ... in spiral order
/**/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generateMatrix(int n)
{
    // all intervals are inclusive, i.e. [left_edge, right_edge]
    // instead of the usual [left_edge, right_edge) - it's convenient this way
    int top_edge = 0;
    int right_edge = n - 1;
    int bottom_edge = n - 1;
    int left_edge = 0;

    int num = 1;
    int row = 0;
    int col = 0;
    vector<vector<int>> matrix(n, vector<int>(n));

    while (left_edge <= right_edge) {
        // go right
        for (col = left_edge; col <= right_edge; ++col) {
            matrix[top_edge][col] = num++;
        }
        ++top_edge;

        // go down
        for (row = top_edge; row <= bottom_edge; ++row) {
            matrix[row][right_edge] = num++;
        }
        --right_edge;

        // go left
        for (col = right_edge; col >= left_edge; --col) {
            matrix[bottom_edge][col] = num++;
        }
        --bottom_edge;

        // go up
        for (row = bottom_edge; row >= top_edge; --row) {
            matrix[row][left_edge] = num++;
        }
        ++left_edge;
    }
    return matrix;
}

//============================================================================//

int main()
{
    while (true) {
        cout << "Enter n:\n";
        int n{};
        cin >> n;

        cout << "Here's your spiral matrix:\n";
        for (auto& row : generateMatrix(n)) {
            for (auto el : row) {
                cout << el << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
