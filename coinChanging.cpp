#include <iostream>

using namespace std;

// Function to find the minimum number of coins and the coins used for a given amount
void minCoins(int coins[], int n, int amount)
{
    // Create an array to store the minimum number of coins for each amount
    int dp[amount + 1];
    dp[0] = 0; // Base case: 0 coins needed for 0 amount

    // Initialize the array with a large value
    for (int i = 1; i <= amount; i++)
    {
        dp[i] = INT_MAX;
    }

    // Create an array to store the last coin used for each amount
    int lastCoin[amount + 1];

    // Dynamic programming to find the minimum number of coins
    for (int i = 1; i <= amount; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                if (dp[i] > dp[i - coins[j]] + 1)
                {
                    dp[i] = dp[i - coins[j]] + 1;
                    lastCoin[i] = coins[j];
                }
            }
        }
    }

    // If dp[amount] is still INT_MAX, it means the amount cannot be made with the given coins
    if (dp[amount] == INT_MAX)
    {
        cout << "The amount cannot be made with the given coins." << endl;
    }
    else
    {
        // Display the result
        cout << "Minimum number of coins needed: " << dp[amount] << endl;
        cout << "Coins used: ";
        while (amount > 0)
        {
            cout << lastCoin[amount] << " ";
            amount -= lastCoin[amount];
        }
        cout << endl;
    }
}

int main()
{
    // Example coins and amount
    int coins[] = {1, 2, 5};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    // Find the minimum number of coins needed and the coins used
    minCoins(coins, n, amount);

    return 0;
}
