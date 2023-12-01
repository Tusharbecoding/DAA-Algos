#include <iostream>

using namespace std;

const int MAX_N = 10; // Maximum number of vertices (adjust as needed)

class Graph
{
private:
    int V;
    int adjMatrix[MAX_N][MAX_N];

public:
    Graph(int vertices) : V(vertices)
    {
        for (int i = 0; i < MAX_N; ++i)
        {
            for (int j = 0; j < MAX_N; ++j)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight);
    void primMaxSpanningTree();
};

void Graph::addEdge(int u, int v, int weight)
{
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

void Graph::primMaxSpanningTree()
{
    int parent[V]; // To store the parent of each vertex in the MST
    int key[V];    // Key values used to pick minimum weight edge in cut

    bool mstSet[V]; // To represent set of vertices included in MST

    // Initialize all keys as -INFINITY and mstSet[] as false
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MIN;
        mstSet[i] = false;
    }

    // Always include the first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the maximum key vertex from the set of vertices not yet included in MST
        int maxKey = INT_MIN;
        int maxKeyVertex;

        for (int v = 0; v < V; v++)
        {
            if (!mstSet[v] && key[v] > maxKey)
            {
                maxKey = key[v];
                maxKeyVertex = v;
            }
        }

        // Add the picked vertex to the MST set
        mstSet[maxKeyVertex] = true;

        // Update key value and parent index of the adjacent vertices
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[maxKeyVertex][v] && !mstSet[v] && adjMatrix[maxKeyVertex][v] > key[v])
            {
                parent[v] = maxKeyVertex;
                key[v] = adjMatrix[maxKeyVertex][v];
            }
        }
    }

    // Print the edges of the maximum spanning tree
    cout << "Edges of Maximum Spanning Tree:" << endl;
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << " Weight: " << adjMatrix[i][parent[i]] << endl;
    }
}

int main()
{
    // Example graph
    Graph graph(4);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 10);
    graph.addEdge(0, 3, 8);
    graph.addEdge(1, 2, 7);
    graph.addEdge(1, 3, 6);

    // Find and display the maximum spanning tree
    graph.primMaxSpanningTree();

    return 0;
}
