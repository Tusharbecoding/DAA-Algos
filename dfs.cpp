#include <iostream>

using namespace std;

class Graph
{
private:
    int vertices;
    int **adjacencyMatrix;

public:
    Graph(int v) : vertices(v)
    {
        adjacencyMatrix = new int *[v];
        for (int i = 0; i < v; ++i)
        {
            adjacencyMatrix[i] = new int[v];
            for (int j = 0; j < v; ++j)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int v, int w)
    {
        adjacencyMatrix[v][w] = 1;
    }

    void DFS(int startVertex)
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            visited[i] = false;
        }

        int *stack = new int[vertices];
        int top = -1;

        visited[startVertex] = true;
        stack[++top] = startVertex;

        while (top != -1)
        {
            int currentVertex = stack[top--];
            cout << currentVertex << " ";

            for (int neighbor = 0; neighbor < vertices; ++neighbor)
            {
                if (adjacencyMatrix[currentVertex][neighbor] == 1 && !visited[neighbor])
                {
                    visited[neighbor] = true;
                    stack[++top] = neighbor;
                }
            }
        }

        delete[] visited;
        delete[] stack;
    }

    ~Graph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};

int main()
{
    // Create a graph
    Graph g(7);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // Perform DFS starting from vertex 0
    cout << "Depth First Search starting from vertex 0: ";
    g.DFS(0);

    return 0;
}
