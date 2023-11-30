#include <iostream>

using namespace std;

// Function to find the maximum value that can be obtained with a given weight limit
int knapsack(int weights[], int values[], int n, int W)
{
    // Create a 2D array to store the maximum value for each subproblem
    int dp[n + 1][W + 1];

    // Dynamic programming to find the maximum value
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main()
{
    // Example weights and values
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = sizeof(weights) / sizeof(weights[0]);
    int W = 5;

    // Find the maximum value for the given weight limit
    int result = knapsack(weights, values, n, W);

    // Display the result
    cout << "Maximum value for the given weight limit: " << result << endl;

    return 0;
}
