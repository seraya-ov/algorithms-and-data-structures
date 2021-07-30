#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;


class Graph {
    vector<vector<int>> graph;
    vector<bool> used;
    vector<int> tin;
    vector<int> fup;
    int cut_size;
    vector<bool> cut_vertexes;
    vector<int> bridges;

    void find_cut_vertex(int v, int p = -1, int timer = 0) {
        used[v] = true;
        tin[v] = timer++;
        fup[v] = tin[v];
        int child = 0;
        for (int u : graph[v]) {
            if (!used[u]) {
                find_cut_vertex(u, v, timer);
                fup[v] = (fup[u] < fup[v]) ? fup[u] : fup[v];
                child++;
                if (fup[u] >= tin[v] && p != -1) {
                    if (!cut_vertexes[v]) {
                        cut_size++;
                    }
                    cut_vertexes[v] = true;
                }
            }
            else if (u != p) {
                fup[v] = (fup[v] < tin[u]) ? fup[v] : tin[u];
            }
        }
        if (p == -1 && child > 1) {
            if (!cut_vertexes[v]) {
                cut_size++;
            }
            cut_vertexes[v] = true;
        }
    }

public:
    Graph(int n_vertexes) : cut_size(0), graph(n_vertexes, vector<int>()), used(n_vertexes, false), tin(n_vertexes, 0), fup(n_vertexes, 0), cut_vertexes(n_vertexes, false) {}
    void push_edge(int i, int j) {
        graph[i].push_back(j);
        graph[j].push_back(i);
    }

    pair <vector<bool>, int> findAllCutvertexes() {
        for (int i = 0; i < graph.size(); i++) {
            if (!used[i]) {
                find_cut_vertex(i);
            }
        }
        return { cut_vertexes, cut_size };
    }

};


int main() {
    int n, m, vb, ve;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> vb >> ve;
        graph.push_edge(vb - 1, ve - 1);
    }
    pair<vector<bool>, int> cut_vertexes = graph.findAllCutvertexes();
    cout << cut_vertexes.second << endl;
    for (int i = 0; i < cut_vertexes.first.size(); i++) {
        if (cut_vertexes.first[i]) {
            cout << i + 1 << endl;
        }
    }
    // system("pause");
    return 0;
}