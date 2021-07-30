#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class OrientedGraph {
    vector<vector<int>> graph, Rgraph;

    bool dfs_visit(int v, vector<char>& color) {
        color[v] = 'G';
        for (int u : graph[v]) {
            if (color[u] == 'G') {
                topsort.clear();
                return false;
            }
            else if (color[u] == 'W') {
                if (!dfs_visit(u, color)) {
                    return false;
                }
            }
        }
        topsort.push_back(v);
        color[v] = 'B';
        return true;
    }
public:
    vector<int> topsort;
    OrientedGraph(int n_vertexes) : graph(n_vertexes, vector<int>()), Rgraph(n_vertexes, vector<int>()) {}
    void push_edge(int i, int j) {
        graph[i].push_back(j);
        Rgraph[j].push_back(i);
    }

    bool doTopsort(vector<char>& color) {
        for (int i = 0; i < color.size(); i++) {
            color[i] = 'W';
        }
        for (int i = 0; i < color.size(); i++) {
            if (color[i] == 'W') {
                if (!dfs_visit(i, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};


int main() {
    int m, n, start, end;
    cin >> n >> m;
    OrientedGraph graph(n);
    vector<char> color(n, 'W');
    for (int i = 0; i < m; i++) {
        cin >> start >> end;
        graph.push_edge(start - 1, end - 1);
    }
    if (!graph.doTopsort(color)) {
        cout << -1 << endl;
    }
    else {
        for (int i = graph.topsort.size() - 1; i >= 0; i--)
            cout << graph.topsort[i] + 1 << ' ';
    }
    return 0;
}