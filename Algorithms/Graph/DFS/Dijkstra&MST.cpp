#include <iostream>
#include <vector>

using namespace std;

class AdjMatrix
{
    int graph[10][10];
    int nVertices;
public:
    AdjMatrix(int);
    void addEdge(int, int, int);
    void showPath(int, int[]);
    void shortestPath(int);
    int minVertex(bool[], int[]);
    void findMST();
};

AdjMatrix::AdjMatrix(int n) {
    nVertices = n;
    for (int i = 0; i < nVertices; i++)
        for (int j = 0; j < nVertices; j++)
            graph[i][j] = 0;
}

void AdjMatrix::addEdge(int u, int v, int weight) {
    graph[u][v] = weight;
}

void AdjMatrix::showPath(int v, int prev[]) {
    while (v != -1) {
        cout << v;
        if (prev[v] != -1)
            cout << "<-";
        else
            cout << "\n";
        v = prev[v];
    }
}

void AdjMatrix::shortestPath(int src) {
    int distance[nVertices];
    int prev[nVertices];
    bool included[nVertices];

    for (int i = 0; i < nVertices; i++) {
        distance[i] = INT_MAX;
        prev[i] = -1;
        included[i] = false;
    }

    distance[src] = 0;
    included[src] = true;

    int u = src;
    int min_d, v_min;
    for (int i = 0; i < nVertices; i++) {
        min_d = -1;
        for (int v = 0; v < nVertices; v++) {
            if (u != v && !included[v]) {
                if (graph[u][v] != 0 && graph[u][v] + distance[u] <= distance[v]) {
                    distance[v] = distance[u] + graph[u][v]; // d[v] = d[u] + w
                    prev[v] = u;
                }
                if (min_d == -1 || min_d > distance[v]) {
                    min_d = distance[v];
                    v_min = v;
                }
            }
        }
        u = v_min;
        included[u] = true;
    }

    for (int v = 0; v < nVertices; v++) {
        cout << "Shortest path from " << src << " to " << v << ": ";
        showPath(v, prev);
        cout << "\n";
    }
}

int AdjMatrix::minVertex(bool included[], int dist[]) {
    int min_dist = -1, v_min;
    for (int v = 0; v < nVertices; v++) {
        if (!included[v] && (min_dist == -1 || dist[v] < min_dist)) {
            min_dist = dist[v];
            v_min = v;
        }
    }

    return v_min;
}

void AdjMatrix::findMST() {
    int prev[nVertices];
    bool included[nVertices];
    int dist[nVertices];

    for (int i = 0; i < nVertices; i++) {
        dist[i] = INT_MAX; 
        prev[i] = -1;
        included[i] = false;
    }

    dist[0] = 0;

    for (int i = 0; i < nVertices - 1; i++) {
        int u = minVertex(included, dist);
        included[u] = true;
        for (int v = 0; v < nVertices; v++)
            if (graph[u][v] != 0 && graph[u][v] < dist[v]) {
                prev[v] = u;
                dist[v] = graph[u][v];
            }
    }

    for (int v = 1; v < nVertices; v++)
        if (prev[v] != -1)
            cout << prev[v] << "->" << v << ": " << graph[prev[v]][v] << "\n";
}

int main() {
    int n = 5;
    AdjMatrix graph(n);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(2, 1, 1);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 3, 4);
    graph.addEdge(2, 4, 5);
    graph.addEdge(4, 3, 1);

    graph.shortestPath(0);
    graph.findMST();
    return 0;
}