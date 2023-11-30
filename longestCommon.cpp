#include <iostream>

using namespace std;

// Function to find the length of the Longest Common Subsequence
int longestCommonSubsequence(char text1[], char text2[], int m, int n)
{
    // Create a 2D array to store the length of LCS for each pair of substrings
    int dp[m + 1][n + 1];

    // Dynamic programming to find the length of LCS
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    // Example strings
    char text1[] = "abecd";
    char text2[] = "ace";

    int m = sizeof(text1) / sizeof(text1[0]) - 1; // subtract 1 for null terminator
    int n = sizeof(text2) / sizeof(text2[0]) - 1; // subtract 1 for null terminator

    // Find the length of the Longest Common Subsequence
    int result = longestCommonSubsequence(text1, text2, m, n);

    // Display the result
    cout << "Length of Longest Common Subsequence: " << result << endl;

    return 0;
}
