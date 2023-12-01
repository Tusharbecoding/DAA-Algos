#include <iostream>

const int MAX_N = 10; // Maximum number of vertices (adjust as needed)

struct Edge
{
    int src, dest, weight;
};

class Graph
{
private:
    int V, E;
    Edge edges[MAX_N * MAX_N];

public:
    Graph(int vertices, int edgesCount) : V(vertices), E(edgesCount) {}

    void addEdge(int u, int v, int weight);
    int kruskalMaxSpanningTree();
};

void Graph::addEdge(int u, int v, int weight)
{
    edges[E].src = u;
    edges[E].dest = v;
    edges[E].weight = weight;
    E++;
}

int findParent(int vertex, int parent[])
{
    if (parent[vertex] == -1)
    {
        return vertex;
    }
    return findParent(parent[vertex], parent);
}

void unionSets(int x, int y, int parent[], int rank[])
{
    int xRoot = findParent(x, parent);
    int yRoot = findParent(y, parent);

    if (rank[xRoot] < rank[yRoot])
    {
        parent[xRoot] = yRoot;
    }
    else if (rank[xRoot] > rank[yRoot])
    {
        parent[yRoot] = xRoot;
    }
    else
    {
        parent[xRoot] = yRoot;
        rank[yRoot]++;
    }
}

int Graph::kruskalMaxSpanningTree()
{
    int parent[MAX_N];
    int rank[MAX_N];

    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        rank[i] = 0;
    }

    // Sort edges in descending order based on weights
    for (int i = 0; i < E; i++)
    {
        for (int j = 0; j < E - 1; j++)
        {
            if (edges[j].weight < edges[j + 1].weight)
            {
                std::swap(edges[j], edges[j + 1]);
            }
        }
    }

    int maxSpanningWeight = 0;

    for (int i = 0; i < E; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        int setU = findParent(u, parent);
        int setV = findParent(v, parent);

        if (setU != setV)
        {
            maxSpanningWeight += weight;
            unionSets(setU, setV, parent, rank);
        }
    }

    return maxSpanningWeight;
}

int main()
{
    // Example graph
    Graph graph(4, 5);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 10);
    graph.addEdge(0, 3, 8);
    graph.addEdge(1, 2, 7);
    graph.addEdge(1, 3, 6);

    // Find and display the maximum spanning tree weight
    int maxSpanningWeight = graph.kruskalMaxSpanningTree();
    std::cout << "Weight of Maximum Spanning Tree: " << maxSpanningWeight << std::endl;

    return 0;
}
