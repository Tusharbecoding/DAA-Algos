#include <iostream>

using namespace std;

// Structure to represent a job
struct Job
{
    char id;
    int deadline;
    int profit;
};

// Function to compare jobs based on their profits (in descending order)
bool jobCompare(const Job &a, const Job &b)
{
    return (a.profit > b.profit);
}

// Function to find the maximum profit job sequence
void jobSequencing(Job jobs[], int n)
{
    // Sort jobs based on profits (in descending order)
    sort(jobs, jobs + n, jobCompare);

    // Find the maximum deadline to create a time slot array
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        maxDeadline = max(maxDeadline, jobs[i].deadline);
    }

    // Initialize a time slot array
    char *result = new char[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
    {
        result[i] = '\0';
    }

    // Fill the time slot array with job IDs
    for (int i = 0; i < n; i++)
    {
        for (int j = min(maxDeadline - 1, jobs[i].deadline - 1); j >= 0; j--)
        {
            if (result[j] == '\0')
            {
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    // Display the result
    cout << "Job Sequence for Maximum Profit: ";
    for (int i = 0; i < maxDeadline; i++)
    {
        if (result[i] != '\0')
        {
            cout << result[i] << " ";
        }
    }
    cout << endl;

    // Clean up dynamic memory
    delete[] result;
}

int main()
{
    // Example jobs
    Job jobs[] = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};

    // Number of jobs
    int n = sizeof(jobs) / sizeof(jobs[0]);

    // Perform job sequencing using greedy approach
    jobSequencing(jobs, n);

    return 0;
}
