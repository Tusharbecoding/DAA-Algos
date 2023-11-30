#include <iostream>

using namespace std;

const int MAX_N = 4; // Maximum number of vertices (adjust as needed)

class Graph
{
private:
    int V;
    int adj[MAX_N][MAX_N];

public:
    Graph(int vertices) : V(vertices)
    {
        for (int i = 0; i < MAX_N; ++i)
        {
            for (int j = 0; j < MAX_N; ++j)
            {
                adj[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void hierholzerAlgorithm();
    bool isValidNextEdge(int u, int v);
};

void Graph::hierholzerAlgorithm()
{
    int circuit[MAX_N * MAX_N];
    int circuitIndex = 0;

    int stack[MAX_N * MAX_N];
    int stackIndex = 0;

    stack[stackIndex++] = 0; // Start from vertex 0

    while (stackIndex != 0)
    {
        int u = stack[stackIndex - 1];

        // Find and remove the next adjacent vertex v
        int v;
        for (v = 0; v < V; v++)
        {
            if (adj[u][v] == 1)
            {
                break;
            }
        }

        // If no adjacent vertices are left, pop the stack and add to the circuit
        if (v == V)
        {
            circuit[circuitIndex++] = u;
            stackIndex--;
        }
        else
        {
            stack[stackIndex++] = v;
            adj[u][v] = 0;
            adj[v][u] = 0;
        }
    }

    // Display the Eulerian circuit
    cout << "Eulerian Circuit: ";
    for (int i = circuitIndex - 1; i >= 0; i--)
    {
        cout << circuit[i] << " ";
    }
    cout << endl;
}

bool Graph::isValidNextEdge(int u, int v)
{
    // Check if vertex v is the only adjacent vertex of u
    int count = 0;
    for (int i = 0; i < V; i++)
    {
        if (adj[u][i] == 1)
        {
            count++;
        }
    }
    if (count == 1)
    {
        return true;
    }

    // If there are multiple adjacent vertices, check if removing edge (u, v) disconnects the graph
    int visited[MAX_N];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    // Count vertices reachable from u before removing edge (u, v)
    count = 0;
    for (int i = 0; i < V; i++)
    {
        if (adj[u][i] == 1)
        {
            visited[i] = true;
            count++;
        }
    }

    // Remove edge (u, v)
    adj[u][v] = 0;
    adj[v][u] = 0;

    // Count vertices reachable from u after removing edge (u, v)
    int countAfterRemoval = 0;
    for (int i = 0; i < V; i++)
    {
        if (visited[i] && adj[u][i] == 1)
        {
            countAfterRemoval++;
        }
    }

    // Restore edge (u, v)
    adj[u][v] = 1;
    adj[v][u] = 1;

    // If removing edge (u, v) disconnects the graph, it is not a valid next edge
    return (countAfterRemoval < count);
}

int main()
{
    // Example graph
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 0);

    // Find and display Eulerian circuit
    graph.hierholzerAlgorithm();

    return 0;
}
