#include <iostream>

using namespace std;

// Function to find the minimum number of scalar multiplications needed for matrix chain multiplication
int matrixChainMultiplication(int dimensions[], int n)
{
    // Create a 2D array to store the minimum number of scalar multiplications for each subproblem
    int dp[n][n];

    // Dynamic programming to find the minimum number of scalar multiplications
    for (int i = 1; i < n; i++)
    {
        dp[i][i] = 0; // Base case: no multiplication needed for a single matrix
    }

    for (int length = 2; length < n; length++)
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n - 1]; // Return the minimum number of scalar multiplications for the entire chain
}

int main()
{
    // Example matrix chain dimensions
    int dimensions[] = {10, 30, 5, 60};

    // Number of matrices
    int n = sizeof(dimensions) / sizeof(dimensions[0]);

    // Find the minimum number of scalar multiplications
    int result = matrixChainMultiplication(dimensions, n);

    // Display the result
    cout << "Minimum number of scalar multiplications: " << result << endl;

    return 0;
}
