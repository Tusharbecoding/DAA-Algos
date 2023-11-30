#include <iostream>

using namespace std;

struct Activity
{
    int start, finish;
};

bool activityCompare(const Activity &a, const Activity &b)
{
    return (a.finish < b.finish);
}

void activitySelectionDP(Activity activities[], int n)
{

    sort(activities, activities + n, activityCompare);

    int *dp = new int[n];
    dp[0] = 1;

    for (int i = 1; i < n; i++)
    {
        dp[i] = 1; // Initialize the count for the current activity

        for (int j = i - 1; j >= 0; j--)
        {
            if (activities[i].start >= activities[j].finish)
            {
                dp[i] = max(dp[i], dp[j] + 1);
                break;
            }
        }
    }

    // Find the maximum value in the dp array
    int maxActivities = *max_element(dp, dp + n);

    // Display the result
    cout << "Maximum number of non-overlapping activities: " << maxActivities << endl;

    // Clean up dynamic memory
    delete[] dp;
}

int main()
{

    Activity activities[] = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};

    int n = sizeof(activities) / sizeof(activities[0]);

    activitySelectionDP(activities, n);

    return 0;
}
