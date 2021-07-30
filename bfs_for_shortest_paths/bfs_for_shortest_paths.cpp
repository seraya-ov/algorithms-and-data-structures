#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
class Graph {
private:
    vector<vector<int>> graph;
public:
    vector<int> path;
    Graph(int size) {
        size = size;
        graph = vector<vector<int>>(size);
        path = vector<int>(size, -1);
    }

    void PushE(int u, int v) {
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    void GetShortestPaths(int A) {
        int size = graph.size();
        vector<int> dist(size, -1);
        queue<int> q;
        int v;
        dist[A] = 0;
        q.push(A);
        while (!(q.empty())) {
            v = q.front();
            q.pop();
            for (int u : graph[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    path[u] = v;
                    q.push(u);
                }
            }
        }
    }
};


int main() {
    int V, E, start, finish, i, j;
    cin >> V >> E >> start >> finish;
    Graph graph(V);
    for (int t = 0; t < E; t++) {
        cin >> i >> j;
        graph.PushE(i - 1, j - 1);
    }
    graph.GetShortestPaths(start - 1);
    int v = finish - 1;
    vector<int> path;
    while (v != -1) {
        path.push_back(v);
        v = graph.path[v];
    }
    reverse(path.begin(), path.end());
    if (path[0] + 1 != start) {
        cout << -1 << endl;
    }
    else {
        cout << path.size() - 1 << endl;
        for (vector<int>::iterator i = path.begin(); i != path.end(); ++i)
            cout << *i + 1 << ' ';
    }
    //system("pause");
    return 0;
}