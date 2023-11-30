#include <iostream>
#include <climits>

using namespace std;

const int MAX_N = 4; // Maximum number of keys (adjust as needed)

// Function to find the minimum cost of a binary search tree
int optimalBST(int keys[MAX_N], int freq[MAX_N])
{
    // Create a 2D array to store the minimum cost for each subproblem
    int dp[MAX_N][MAX_N];

    // Dynamic programming to find the minimum cost
    for (int i = 0; i < MAX_N; i++)
    {
        dp[i][i] = freq[i];
    }

    for (int length = 2; length <= MAX_N; length++)
    {
        for (int i = 0; i <= MAX_N - length; i++)
        {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            // Try making each key the root and recursively calculate the cost
            for (int k = i; k <= j; k++)
            {
                int cost = ((k > i) ? dp[i][k - 1] : 0) +
                           ((k < j) ? dp[k + 1][j] : 0) +
                           freq[k];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][MAX_N - 1];
}

int main()
{
    // Example keys and frequencies
    int keys[MAX_N] = {10, 20, 30, 40};
    int freq[MAX_N] = {4, 2, 6, 3};

    // Find the minimum cost of a binary search tree
    int result = optimalBST(keys, freq);

    // Display the result
    cout << "Minimum cost of Optimal Binary Search Tree: " << result << endl;

    return 0;
}
