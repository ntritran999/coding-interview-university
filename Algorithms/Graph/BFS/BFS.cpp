#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class AdjList
{
    vector<vector<int>> graph;
    int nVertices;
public:
    AdjList(int);
    void addEdge(int, int);
    void BFS(int);
};

AdjList::AdjList(int n) {
    graph.resize(n);
    nVertices = n;
}

void AdjList::addEdge(int u, int v) {
    graph[u].push_back(v);
}

void AdjList::BFS(int u) {
    vector<bool> visited(nVertices);
    for (int i = 0; i < nVertices; i++)
        visited[i] = false;

    queue<int> q;
    q.push(u);
    visited[u] = true;

    while(!q.empty()) {
        u = q.front();
        cout << u << " ";
        q.pop();
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

class AdjMatrix
{
    int graph[10][10];
    int nVertices;
public:
    AdjMatrix(int);
    void addEdge(int, int);
    void BFS(int);
};

AdjMatrix::AdjMatrix(int n) {
    nVertices = n;
    for (int i = 0; i < nVertices; i++)
        for (int j = 0; j < nVertices; j++)
            graph[i][j] = 0;
}

void AdjMatrix::addEdge(int u, int v) {
    graph[u][v] = 1;
}

void AdjMatrix::BFS(int u) {
    vector<bool> visited(nVertices);
    for (int i = 0; i < nVertices; i++)
        visited[i] = false;

    queue<int> q;
    q.push(u);
    visited[u] = true;

    while(!q.empty()) {
        u = q.front();
        cout << u << " ";
        q.pop();
        for (int v = 0; v < nVertices; v++) {
            if (!visited[v] && graph[u][v] == 1) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
        int n = 6;

    //-----Adjacency List Test------
    AdjList graph1(n);

    graph1.addEdge(0, 1);
    graph1.addEdge(0, 2);
    graph1.addEdge(1, 3);
    graph1.addEdge(1, 5);
    graph1.addEdge(3, 4);
    graph1.BFS(0);
    cout << "\n\n";

    //-----Adjacency Matrx Test------
    AdjMatrix graph2(n);

    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 3);
    graph2.addEdge(1, 5);
    graph2.addEdge(3, 4);
    graph2.BFS(0);
}