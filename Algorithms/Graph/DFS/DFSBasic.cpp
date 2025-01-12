#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class AdjList
{
    vector<vector<int>> graph;
    int nVertices;
public:
    AdjList(int);
    void addEdge(int, int);
    void recursiveDFS(int, vector<bool>&);
    void iterativeDFS(int);
};

AdjList::AdjList(int n) {
    graph.resize(n);
    nVertices = n;
}

void AdjList::addEdge(int u, int v) {
    graph[u].push_back(v);
}

void AdjList::recursiveDFS(int u, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int i = 0; i < graph[u].size(); i++) {
        if (!visited[graph[u][i]])
            recursiveDFS(graph[u][i], visited);
    }
}

void AdjList::iterativeDFS(int u) {
    vector<bool> visited(nVertices);
    for (int i = 0; i < nVertices; i++)
        visited[i] = false;

    stack<int> s;
    s.push(u);
    visited[u] = true;

    while (!s.empty()) {
        u = s.top();
        cout << u << " ";
        s.pop();
        for (int i = graph[u].size() - 1; i >= 0; i--) {
            int v = graph[u][i];
            if (!visited[v]) {
                visited[v] = true;
                s.push(v);          
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
    void recursiveDFS(int, vector<bool>&);
    void iterativeDFS(int);
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

void AdjMatrix::recursiveDFS(int u, vector<bool>& visited) {
    cout << u << " ";
    visited[u] = true;
    for (int v = 0; v < nVertices; v++)
        if (!visited[v] && graph[u][v] == 1)
            recursiveDFS(v, visited);
}

void AdjMatrix::iterativeDFS(int u) {
    vector<bool> visited(nVertices);
    for (int i = 0; i < nVertices; i++)
        visited[i] = false;

    stack<int> s;
    s.push(u);
    visited[u] = true;

    while(!s.empty()) {
        u = s.top();
        cout << u << " ";
        s.pop();
        for (int v = nVertices; v >= 0; v--)
            if (!visited[v] && graph[u][v] == 1) {
                visited[v] = true;
                s.push(v);
            }
    }
}

int main() {
    int n = 6;

    //-----Adjacency List Test------
    AdjList graph1(n);
    vector<bool> visited(n);
    for (int i = 0; i < n; i++)
        visited[i] = false;

    graph1.addEdge(0, 1);
    graph1.addEdge(0, 2);
    graph1.addEdge(1, 3);
    graph1.addEdge(1, 5);
    graph1.addEdge(3, 4);
    graph1.recursiveDFS(0, visited);
    cout << "\n";
    graph1.iterativeDFS(0);
    cout << "\n";

    //-----Adjacency Matrx Test------
    AdjMatrix graph2(n);
    visited.clear();
    for (int i = 0; i < n; i++)
        visited[i] = false;

    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 3);
    graph2.addEdge(1, 5);
    graph2.addEdge(3, 4);
    graph2.recursiveDFS(0, visited);
    cout << "\n";
    graph2.iterativeDFS(0);
}