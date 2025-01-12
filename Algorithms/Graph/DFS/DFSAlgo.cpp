#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class AdjMatrix
{
    int graph[10][10];
    int nVertices;
    void reverse();
    bool isCyclicUtil(int, bool[], bool[]);
    void DFSUtil(int, vector<bool>&, stack<int>&);
    void DFSReverse(int, vector<bool>&, vector<int>&);
    bool DFSColor(int, int, vector<int>&);
public:
    AdjMatrix(int);
    void addEdge(int, int);
    bool isCyclic();
    void topoSort();
    void showSCC();
    bool isBipartite();
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

bool AdjMatrix::isCyclicUtil(int v, bool recStack[], bool visited[]) {
    visited[v] = recStack[v] = true;

    for (int u = 0; u < nVertices; u++)
        if (!visited[u] && graph[v][u] != 0) {
            if (isCyclicUtil(u, recStack, visited))
                return true;
            else if (recStack[u])
                return true;
        }

    recStack[v] = false;
    return false;
}

bool AdjMatrix::isCyclic() {
    bool recStack[nVertices];
    bool visited[nVertices];

    for (int i = 0; i < nVertices; i++)
        recStack[i] = visited[i] = false;

    for (int v = 0; v < nVertices; v++)
        if (!visited[v] && isCyclicUtil(v, recStack, visited))
            return true;

    return false;
}

void AdjMatrix::topoSort() {
    if (isCyclic()) {
        cout << "Graph contains cycle.\n";
        return;
    }

    int in_degrees[nVertices] = {0};
    for (int u = 0; u < nVertices; u++)
        for (int v = 0; v < nVertices; v++)
            if (graph[u][v] != 0)
                in_degrees[v]++;

    queue<int> q;
    for (int v = 0; v < nVertices; v++)
        if (in_degrees[v] == 0)
            q.push(v);
        
    while (!q.empty()) {
        int u = q.front();
        cout << u << " ";
        q.pop();

        for (int v = 0; v < nVertices; v++) {
            if (graph[u][v] != 0) {
                in_degrees[v]--;
                
                if (in_degrees[v] == 0)
                    q.push(v);
            }
        }
    }
}

void AdjMatrix::reverse() {
    for (int i = 0; i < nVertices; i++)
        for (int j = 0; j < nVertices; j++)
            swap(graph[i][j],graph[j][i]);
}

void AdjMatrix::DFSUtil(int v, vector<bool>& visited, stack<int>& s) {
    visited[v] = true;

    for (int u = 0; u < nVertices; u++)
        if (!visited[u] && graph[v][u] != 0)
            DFSUtil(u, visited, s);

    s.push(v);
}

void AdjMatrix::DFSReverse(int v, vector<bool>& visited, vector<int>& set) {
    visited[v] = true;
    set.push_back(v);

    for (int u = 0; u < nVertices; u++)
        if (!visited[u] && graph[v][u] != 0)
            DFSReverse(u, visited, set);
}

void AdjMatrix::showSCC() {
    vector<bool> visited(nVertices, false);

    stack<int> s;
    for (int v = 0; v < nVertices; v++)
        if (!visited[v])
            DFSUtil(v, visited, s);

    reverse();

    for (int i = 0; i < nVertices; i++)
        visited[i] = false;
    vector<vector<int>> scc_list;
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            vector<int> scc;
            DFSReverse(u, visited, scc);
            scc_list.push_back(scc);
        }
    }

    for (int i = 0; i < scc_list.size(); i++) {
        cout << "Strongly connect component " << i + 1 << ": ";
        for (int j = 0; j < scc_list[i].size(); j++)
            cout << scc_list[i][j] << " ";
        cout << "\n";
    }
}

bool AdjMatrix::DFSColor(int v, int color, vector<int>& colors) {
    colors[v] = color;

    for (int u = 0; u < nVertices; u++)
        if (colors[u] == -1 && graph[v][u] != 0) {
            if (!DFSColor(u, 1, colors))
                return false;
            if (colors[u] == color)
                return false;
        }
    return true;
}

bool AdjMatrix::isBipartite() {
    vector<int> colors(nVertices, -1); // -1 == uncolored

    for (int v = 0; v < nVertices; v++)
        if (colors[v] == -1)
            if (!DFSColor(v, 0, colors))
                return false;

    return true;
}

class UndirectedAdjMatrix
{
    int graph[10][10];
    int nVertices;
    void DFSUtil(int, vector<bool>&);
public:
    UndirectedAdjMatrix(int);
    void addEdge(int, int);
    int countCC();
};

UndirectedAdjMatrix::UndirectedAdjMatrix(int n) {
    nVertices = n;
    for (int i = 0; i < nVertices; i++)
        for (int j = 0; j < nVertices; j++)
            graph[i][j] = 0;
}

void UndirectedAdjMatrix::addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void UndirectedAdjMatrix::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;

    for (int u = 0; u < nVertices; u++)
        if (!visited[u] && graph[v][u] != 0)
            DFSUtil(u, visited);
}

int UndirectedAdjMatrix::countCC() {
    vector<bool> visited(nVertices, false);

    int cnt = 0;
    for (int v = 0; v < nVertices; v++) {
        if (!visited[v]) {
            DFSUtil(v, visited);
            cnt++;
        }
    }
    return cnt;
}

int main() {
    int n = 6;
    AdjMatrix graph(n);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(4, 5);
    graph.addEdge(5, 1);
    graph.addEdge(5, 2);

    cout << "Topological sort of first graph: ";
    graph.topoSort();
    cout << "\n";
    graph.showSCC();
    cout << "\n";
    cout << "Is first graph bipartite: " << ((graph.isBipartite()) ? "Yes" : "No");
    cout << "\n\n";

    // ---------------------------
    UndirectedAdjMatrix graph1(n);
    graph1.addEdge(0, 1);
    graph1.addEdge(1, 2);
    graph1.addEdge(2, 3);
    graph1.addEdge(4, 5);
    graph1.addEdge(5, 1);
    graph1.addEdge(5, 2);
    cout << "Number of connected components of second graph: " << graph1.countCC() << "\n";
    return 0;
}