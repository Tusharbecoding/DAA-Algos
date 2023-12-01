#include <iostream>
#include <cstring>

const int MAX_V = 100; // Maximum number of vertices (adjust as needed)

class FordFulkerson
{
private:
    int graph[MAX_V][MAX_V];
    int parent[MAX_V];

public:
    FordFulkerson();
    void addEdge(int u, int v, int capacity);
    int fordFulkerson(int source, int sink);
};

FordFulkerson::FordFulkerson()
{
    // Initialize the graph
    memset(graph, 0, sizeof(graph));
}

void FordFulkerson::addEdge(int u, int v, int capacity)
{
    graph[u][v] = capacity;
}

int FordFulkerson::fordFulkerson(int source, int sink)
{
    int maxFlow = 0;

    while (true)
    {
        memset(parent, -1, sizeof(parent));

        int queue[MAX_V];
        int front = 0, rear = 0;

        queue[rear++] = source;
        parent[source] = source;

        while (front < rear)
        {
            int current = queue[front++];
            for (int next = 0; next < MAX_V; next++)
            {
                if (parent[next] == -1 && graph[current][next] > 0)
                {
                    queue[rear++] = next;
                    parent[next] = current;
                }
            }
        }

        if (parent[sink] == -1)
        {
            break; // No augmenting path found
        }

        int pathFlow = INT_MAX;

        // Find the minimum capacity along the augmenting path
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            pathFlow = std::min(pathFlow, graph[u][v]);
        }

        // Update the capacities and reverse edges along the augmenting path
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    FordFulkerson fordFulkerson;

    // Example graph
    fordFulkerson.addEdge(0, 1, 10);
    fordFulkerson.addEdge(0, 2, 5);
    fordFulkerson.addEdge(1, 2, 15);
    fordFulkerson.addEdge(1, 3, 10);
    fordFulkerson.addEdge(2, 3, 10);

    int source = 0;
    int sink = 3;

    int maxFlow = fordFulkerson.fordFulkerson(source, sink);

    std::cout << "Maximum Flow: " << maxFlow << std::endl;

    return 0;
}
