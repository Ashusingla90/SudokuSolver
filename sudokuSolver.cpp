#include <iostream>
#include <vector>

using namespace std;

class SudokuSolver {
public:
    // Function to check if placing a digit is safe
    bool isSafe(int digit, int row, int col, const vector<vector<int>>& board) {
        // Check the row
        for (int k = 0; k < 9; k++) {
            if (board[row][k] == digit) {
                return false;
            }
        }

        // Check the column
        for (int k = 0; k < 9; k++) {
            if (board[k][col] == digit) {
                return false;
            }
        }

        // Check the 3x3 subgrid
        int startRow = row - (row % 3);
        int startCol = col - (col % 3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + startRow][j + startCol] == digit) {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to solve the Sudoku using backtracking
    bool solveSudoku(vector<vector<int>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // Find an empty cell (represented by 0)
                if (board[i][j] == 0) {
                    for (int digit = 1; digit <= 9; digit++) {
                        if (isSafe(digit, i, j, board)) {
                            board[i][j] = digit; // Place the digit
                            if (solveSudoku(board)) {
                                return true; // If solved, return true
                            }
                            board[i][j] = 0; // Backtrack
                        }
                    }
                    return false; // No valid number found
                }
            }
        }
        return true; // Sudoku solved
    }

    // Function to print the Sudoku board
    void printBoard(const vector<vector<int>>& board) {
        for (const auto& row : board) {
            for (int num : row) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<int>> board(9, vector<int>(9, 0));
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;

    // Input the Sudoku puzzle
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    SudokuSolver solver;
    if (solver.solveSudoku(board)) {
        cout << "Sudoku solved successfully!" << endl;
        solver.printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}