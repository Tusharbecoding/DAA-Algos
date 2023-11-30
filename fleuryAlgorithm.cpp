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

    bool isBridge(int u, int v);

    void removeEdge(int u, int v);

    void fleuryAlgorithm(int startVertex);
};

bool Graph::isBridge(int u, int v)
{
    // Count the number of vertices reachable from u
    int count1 = 0;
    for (int vertex = 0; vertex < V; ++vertex)
    {
        if (adj[u][vertex] && vertex != v)
        {
            count1++;
        }
    }

    // Remove edge (u, v) and count the number of vertices reachable from u after removal
    removeEdge(u, v);

    int count2 = 0;
    for (int vertex = 0; vertex < V; ++vertex)
    {
        if (adj[u][vertex] && vertex != v)
        {
            count2++;
        }
    }

    // Restore the edge (u, v)
    addEdge(u, v);

    // If the removal of edge (u, v) disconnects the graph, it is a bridge
    return (count1 > count2);
}

void Graph::removeEdge(int u, int v)
{
    adj[u][v] = 0;
    adj[v][u] = 0;
}

void Graph::fleuryAlgorithm(int startVertex)
{
    int u = startVertex;

    // Find a vertex with an odd degree as the starting point
    for (int i = 0; i < V; i++)
    {
        int degree = 0;
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j])
            {
                degree++;
            }
        }
        if (degree % 2 != 0)
        {
            u = i;
            break;
        }
    }

    int stack[MAX_N * MAX_N];
    int top = -1;
    int path[MAX_N * MAX_N];
    int pathIndex = 0;

    stack[++top] = u;

    while (top >= 0)
    {
        u = stack[top];

        // If there are no more adjacent vertices, backtrack
        bool found = false;
        for (int i = 0; i < V; i++)
        {
            if (adj[u][i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            path[pathIndex++] = u;
            top--;
        }
        else
        {
            // If u has only one adjacent vertex, proceed
            int v = -1;
            for (int i = 0; i < V; i++)
            {
                if (adj[u][i])
                {
                    v = i;
                    break;
                }
            }

            path[pathIndex++] = u;
            top--;
            removeEdge(u, v);
            stack[++top] = v;
        }
    }

    // Display the Eulerian path
    cout << "Eulerian Path or Circuit: ";
    for (int i = 0; i < pathIndex; i++)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}

int main()
{
    // Example graph
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    // Find and display Eulerian path or circuit
    graph.fleuryAlgorithm(0);

    return 0;
}
