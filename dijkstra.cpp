#include <iostream>

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
    void dijkstra(int startVertex);
};

void Graph::addEdge(int u, int v, int weight)
{
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

void Graph::dijkstra(int startVertex)
{
    int distance[MAX_N]; // To store the shortest distance from startVertex to each vertex
    bool visited[MAX_N]; // To mark whether a vertex is visited or not

    for (int i = 0; i < V; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[startVertex] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        int minDistance = INT_MAX;
        int minVertex;

        // Find the vertex with the minimum distance value among the vertices not yet processed
        for (int j = 0; j < V; j++)
        {
            if (!visited[j] && distance[j] <= minDistance)
            {
                minDistance = distance[j];
                minVertex = j;
            }
        }

        visited[minVertex] = true;

        // Update the distance value of the neighboring vertices of the picked vertex
        for (int k = 0; k < V; k++)
        {
            if (!visited[k] && adjMatrix[minVertex][k] && distance[minVertex] != INT_MAX &&
                distance[minVertex] + adjMatrix[minVertex][k] < distance[k])
            {
                distance[k] = distance[minVertex] + adjMatrix[minVertex][k];
            }
        }
    }

    // Print the shortest distances from startVertex to all other vertices
    std::cout << "Shortest Distances from Vertex " << startVertex << ":" << std::endl;
    for (int i = 0; i < V; i++)
    {
        std::cout << "To " << i << ": " << distance[i] << std::endl;
    }
}

int main()
{
    // Example graph
    Graph graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 10);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 9);
    graph.addEdge(2, 4, 12);
    graph.addEdge(3, 4, 6);
    graph.addEdge(3, 5, 8);
    graph.addEdge(4, 5, 7);

    // Find and display shortest distances from Vertex 0
    graph.dijkstra(0);

    return 0;
}
