/*
  https://leetcode.com/problems/game-of-life/

  The great John Conway's Game of Life
  Given the current state of the 'm x n' grid 'board', return the next state
/**/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// returns the state of the cell at 'row, col' at the beginning of the step
int restore(const vector<vector<int>>& board, int row, int col)
{
    return board[row][col] % 2 != 0;
}

// returns the number of neighbours of cell at 'row, col' which are alive
int count_neighbours(const vector<vector<int>>& board, int row, int col)
{
    int row_from = max(0, row - 1);
    int col_from = max(0, col - 1);
    int row_to   = min((int)board.size() - 1, row + 1);
    int col_to   = min((int)board[0].size() - 1, col + 1);

    int neighbour_count = 0;
    for (int i = row_from; i <= row_to; ++i) {
        for (int j = col_from; j <= col_to; ++j) {
            if (restore(board, i, j) == 1) ++neighbour_count;
        }
    }
    return neighbour_count - board[row][col];
}

// converts each cell from intermediate state to final state
// 2 -> 1, -1 -> 0
void normalize(vector<vector<int>>& board)
{
    for (auto& row : board) {
        for (auto& el : row) {
            if (el == -1) el = 0;
            else if (el == 2) el = 1;
        }
    }
}

void gameOfLife(vector<vector<int>>& board)
{
    int num_rows = board.size();
    int num_cols = board[0].size();

    // first pass: we check each cell and update their values acoording to the rules;
    // however, what we write into cells are not 1s and 0s
    // since we wanna preserve old values, we use the following rule:
    //    - if the cell's value wasn't gonna change, we don't change it
    //    - if the cell was 0 and was gonna become 1, we set it to 2
    //    - if the cell was 1 and was gonna become 0, we set it to -1
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            int neighbour_count = count_neighbours(board, i, j);

            // underpopulation
            if (neighbour_count < 2) {
                board[i][j] = (board[i][j] == 0) ? 0 : -1;
                continue;
            }
            // 3 neighbours = sexy time, great success!
            if (neighbour_count == 3) {
                board[i][j] = (board[i][j] == 1) ? 1 : 2;
                continue;
            }
            // overpopulation
            if (neighbour_count > 3) {
                board[i][j] = (board[i][j] == 1) ? -1 : 0;
                continue;
            }
        }
    }
    // second pass: normalizing the board and we're done
    normalize(board);
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

        cout << "Enter the board!\n";
        vector<vector<int>> board;
        while (m-- > 0) {
            vector<int> row;
            for (int i = 0; i < n; ++i) {
                int x{ };
                cin >> x;
                row.push_back(x);
            }
            board.push_back(move(row));
        }

        gameOfLife(board);
        cout << "Here's the next step:\n";
        for (auto& row : board) {
            for (int el : row) {
                cout << el << ' ';
            }
            cout << '\n';
        }
        
        while (true) {
            cout << "Want to see some more steps? (y/n)\n";
            char answer = 'n';
            cin >> answer;
            if (answer != 'y') break;

            gameOfLife(board);
            cout << "Here's the next permutation\n";
            for (auto& row : board) {
                for (int el : row) {
                    cout << el << ' ';
                }
                cout << '\n';
            }
        }
    }

    return 0;
}
