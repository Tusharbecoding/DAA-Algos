#include <iostream>

const int MAX_V = 100; // Maximum number of vertices (adjust as needed)
const int INF = 9999;  // Infinity value for uninitialized distances

class FloydWarshall
{
private:
    int graph[MAX_V][MAX_V];

public:
    FloydWarshall();
    void addEdge(int u, int v, int weight);
    void floydWarshall();
    void printSolution();
};

FloydWarshall::FloydWarshall()
{
    // Initialize the graph with INF distances
    for (int i = 0; i < MAX_V; i++)
    {
        for (int j = 0; j < MAX_V; j++)
        {
            graph[i][j] = INF;
        }
        graph[i][i] = 0; // Distance to itself is 0
    }
}

void FloydWarshall::addEdge(int u, int v, int weight)
{
    graph[u][v] = weight;
}

void FloydWarshall::floydWarshall()
{
    for (int k = 0; k < MAX_V; k++)
    {
        for (int i = 0; i < MAX_V; i++)
        {
            for (int j = 0; j < MAX_V; j++)
            {
                if (graph[i][k] + graph[k][j] < graph[i][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

void FloydWarshall::printSolution()
{
    std::cout << "Shortest distances between every pair of vertices:" << std::endl;
    for (int i = 0; i < MAX_V; i++)
    {
        for (int j = 0; j < MAX_V; j++)
        {
            if (graph[i][j] == INF)
            {
                std::cout << "INF ";
            }
            else
            {
                std::cout << graph[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main()
{
    FloydWarshall floydWarshall;

    // Example graph
    floydWarshall.addEdge(0, 1, 3);
    floydWarshall.addEdge(0, 2, 7);
    floydWarshall.addEdge(1, 0, 8);
    floydWarshall.addEdge(1, 2, 2);
    floydWarshall.addEdge(2, 0, 5);
    floydWarshall.addEdge(2, 1, 1);

    floydWarshall.floydWarshall();
    floydWarshall.printSolution();

    return 0;
}
