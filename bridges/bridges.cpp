#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct Edge {
    int from, to, edge_id;
};
class Graph {
    vector<vector<Edge>> graph;
    vector<bool> used;
    vector<int> tin;
    vector<int> fup;
    vector<int> bridges;

    void find_bridges(Edge e, int timer = 0) {
        int v = e.to;
        used[v] = true;
        tin[v] = timer++;
        fup[v] = tin[v];
        for (Edge u : graph[v]) {
            if (!used[u.to]) {
                find_bridges(u, timer);
                fup[v] = (fup[u.to] < fup[v]) ? fup[u.to] : fup[v];
            }
            else if (u.edge_id != e.edge_id) {
                fup[v] = (fup[v] < tin[u.to]) ? fup[v] : tin[u.to];
            }
        }
        if (e.edge_id != -1 && fup[v] == tin[v]) {
            bridges.push_back(e.edge_id);
        }
    }

public:
    Graph(int n_vertexes) : graph(n_vertexes), used(n_vertexes, false), tin(n_vertexes, 0), fup(n_vertexes, 0) {}
    void push_edge(Edge i) {
        graph[i.from].push_back(i);
        graph[i.to].push_back({ i.to, i.from, i.edge_id });
    }

    vector<int> findAllBridges() {
        for (int i = 0; i < graph.size(); i++) {
            find_bridges({ -1, i, -1 });
        }
        return bridges;
    }
};


int main() {
    int n, m, vb, ve;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> vb >> ve;
        graph.push_edge({ vb - 1, ve - 1, i });
    }
    vector<int> bridges = graph.findAllBridges();
    cout << bridges.size() << endl;
    sort(bridges.begin(), bridges.end());
    for (int i = 0; i < bridges.size(); i++) {
        cout << bridges[i] + 1 << endl;
    }
    //system("pause");
    return 0;
}