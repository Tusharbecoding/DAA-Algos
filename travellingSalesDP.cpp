#include <iostream>

using namespace std;

const int MAX_N = 15; // Maximum number of cities (adjust as needed)

// Function to calculate the distance between two cities
double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to find the minimum cost of visiting all cities in a TSP tour
double tsp(int n, double graph[MAX_N][2], double dp[1 << MAX_N][MAX_N], int mask, int pos)
{
    if (mask == (1 << n) - 1)
    {
        // All cities have been visited, return the cost to return to the starting city
        return graph[pos][0];
    }

    // If the result is already calculated, return it
    if (dp[mask][pos] != -1.0)
    {
        return dp[mask][pos];
    }

    double minCost = INT_MAX;

    // Try visiting each unvisited city
    for (int next = 0; next < n; next++)
    {
        if ((mask & (1 << next)) == 0)
        { // Check if the city has not been visited
            double newCost = graph[pos][1] + tsp(n, graph, dp, mask | (1 << next), next);
            minCost = min(minCost, newCost);
        }
    }

    // Memoize the result
    dp[mask][pos] = minCost;

    return minCost;
}

// Function to solve the TSP using dynamic programming
double solveTSP(int n, double graph[MAX_N][2])
{
    // Initialize a 2D array for memoization
    double dp[1 << MAX_N][MAX_N];

    // Initialize the memoization array
    for (int i = 0; i < (1 << MAX_N); i++)
    {
        for (int j = 0; j < MAX_N; j++)
        {
            dp[i][j] = -1.0;
        }
    }

    // Start the TSP from the first city (index 0)
    return tsp(n, graph, dp, 1, 0);
}

int main()
{
    // Example graph with city coordinates
    double graph[MAX_N][2] = {
        {0, 0}, {2, 10}, {5, 8}, {8, 5}, {10, 2}};

    // Number of cities
    int n = sizeof(graph) / sizeof(graph[0]);

    // Find the minimum cost of visiting all cities in a TSP tour
    double result = solveTSP(n, graph);

    // Display the result
    cout << "Minimum cost of TSP tour: " << result << endl;

    return 0;
}
