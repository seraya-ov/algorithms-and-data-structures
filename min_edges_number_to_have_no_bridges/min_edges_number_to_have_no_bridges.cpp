#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct Edge {
    int from, to, edge_id;
    bool bridge;
};
class Graph {
    vector<vector<Edge>> graph;
    vector<int> colors;
    int comp_num;
    vector<bool> used;
    vector<int> tin;
    vector<int> fup;
    vector<Edge> bridges;

    void find_bridges(Edge e, int whereisedge, int timer = 0) {
        int v = e.to;
        used[v] = true;
        tin[v] = timer++;
        fup[v] = tin[v];
        for (int t = 0; t < graph[v].size(); t++) {
            Edge u = graph[v][t];
            if (!used[u.to]) {
                find_bridges(u, t, timer);
                fup[v] = (fup[u.to] < fup[v]) ? fup[u.to] : fup[v];
            }
            else if (u.edge_id != e.edge_id) {
                fup[v] = (fup[v] < tin[u.to]) ? fup[v] : tin[u.to];
            }
        }
        if (e.edge_id != -1 && fup[v] == tin[v]) {
            e.bridge = true;
            graph[e.from][whereisedge].bridge = true;
            for (int h = 0; h < graph[e.to].size(); h++) {
                Edge ee = graph[e.to][h];
                if (ee.edge_id == e.edge_id) {
                    graph[e.to][h].bridge = true;
                    break;
                }
            }
            bridges.push_back(e);
        }
    }

    void DFSforComponent(int v, int comp_num) {
        colors[v] = comp_num;
        for (Edge u : graph[v]) {
            if (!(u.bridge) && colors[u.to] == -1) {
                DFSforComponent(u.to, comp_num);
            }
        }
    }

    void findComponents() {
        comp_num = 0;
        int size = graph.size();
        for (int i = 0; i < size; i++) {
            if (colors[i] == -1) {
                DFSforComponent(i, comp_num++);
            }
        }
    }

    int makeTree() {
        vector<vector<int>> tree(comp_num);
        for (Edge i : bridges) {
            tree[colors[i.from]].push_back(colors[i.to]);
            tree[colors[i.to]].push_back(colors[i.from]);
        }
        int min_roads_num = 0;
        for (int i = 0; i < comp_num; i++) {
            if (tree[i].size() == 1) {
                min_roads_num++;
            }
        }
        if (min_roads_num % 2) {
            return (min_roads_num / 2 + 1);
        }
        return min_roads_num / 2;
    }

public:
    Graph(int n_vertexes) : colors(n_vertexes, -1), graph(n_vertexes), used(n_vertexes, false), tin(n_vertexes, 0), fup(n_vertexes, 0) {}
    void push_edge(Edge i) {
        graph[i.from].push_back(i);
        graph[i.to].push_back({ i.to, i.from, i.edge_id, false });
    }

    int minEdgesNumToHaveNoBridges() {
        for (int i = 0; i < graph.size(); i++) {
            find_bridges({ -1, i, -1, false }, -1);
        }
        findComponents();
        return makeTree();
    }
};


int main() {
    int n, m, vb, ve;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> vb >> ve;
        graph.push_edge({ vb - 1, ve - 1, i, false });
    }
    cout << graph.minEdgesNumToHaveNoBridges() << endl;
    //system("pause");
    return 0;
}