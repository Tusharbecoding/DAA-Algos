#include <iostream>

using namespace std;

const int MAX_N = 10; // Maximum value of N (adjust as needed)

class NQueens
{
private:
    int N;
    int board[MAX_N][MAX_N];

public:
    NQueens(int size) : N(size)
    {
        for (int i = 0; i < MAX_N; ++i)
        {
            for (int j = 0; j < MAX_N; ++j)
            {
                board[i][j] = 0;
            }
        }
    }

    void solveNQueens();
    bool solveNQueensUtil(int row);
    bool isSafe(int row, int col);
    void printBoard();
};

void NQueens::solveNQueens()
{
    if (!solveNQueensUtil(0))
    {
        cout << "Solution does not exist." << endl;
    }
    else
    {
        printBoard();
    }
}

bool NQueens::solveNQueensUtil(int row)
{
    if (row == N)
    {
        return true;
    }

    for (int col = 0; col < N; col++)
    {
        if (isSafe(row, col))
        {
            board[row][col] = 1;

            if (solveNQueensUtil(row + 1))
            {
                return true;
            }

            board[row][col] = 0; // Backtrack if placing a queen in the current position doesn't lead to a solution
        }
    }

    return false;
}

bool NQueens::isSafe(int row, int col)
{
    // Check for queens in the same column
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
        {
            return false;
        }
    }

    // Check for queens in the left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }

    // Check for queens in the right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }

    return true;
}

void NQueens::printBoard()
{
    cout << "Solution:" << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nPositions of Queens (row, col):" << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] == 1)
            {
                cout << "(" << i << ", " << j << ") ";
            }
        }
    }
    cout << endl;
}

int main()
{
    // Example for N = 4
    int N = 4;
    NQueens nQueens(N);
    nQueens.solveNQueens();

    return 0;
}
