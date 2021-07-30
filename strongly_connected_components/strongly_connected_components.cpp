#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class OrientedGraph {
    vector<vector<int>> graph, Rgraph;
    vector<bool> used;
    int comp_cnt;

    void get_order(int v, stack<int>& order) {
        used[v] = true;
        for (int u : graph[v]) {
            if (!used[u]) {
                get_order(u, order);
            }
        }
        order.push(v);
    }

    void mark(int v, vector<int>& components, int color) {
        components[v] = color;
        for (int u : Rgraph[v]) {
            if (components[u] == -1) {
                mark(u, components, color);
            }
        }
    }

public:
    OrientedGraph(int n_vertexes) : graph(n_vertexes, vector<int>()), Rgraph(n_vertexes, vector<int>()), used(n_vertexes, false) {}
    void push_edge(int i, int j) {
        graph[i].push_back(j);
        Rgraph[j].push_back(i);
    }

    vector<int> find_strong_components() {
        std::stack<int> order;
        for (int i = 0; i < graph.size(); ++i) {
            if (!used[i]) {
                get_order(i, order);
            }
        }
        vector<int> components(graph.size(), -1);
        int cnt = 0;
        while (!order.empty()) {
            int v = order.top();
            order.pop();
            if (components[v] == -1) {
                mark(v, components, cnt++);
            }
        }
        comp_cnt = cnt;
        return components;
    }

    int comp_edges(vector<int> components) {
        vector<vector<bool>> edges(comp_cnt, vector<bool>(comp_cnt, false));
        int edges_cnt = 0;
        for (int i = 0; i < components.size(); i++) {
            for (int j : graph[i]) {
                if (components[j] != components[i] && edges[components[i]][components[j]] == false) {
                    edges[components[i]][components[j]] = true;
                    edges_cnt++;
                }
            }
        }
        return edges_cnt + 1;
    }
};


int main() {
    int m, n, start, end;
    cin >> n >> m;
    OrientedGraph graph(n);
    vector<char> colors(n, 'W');
    for (int i = 0; i < m; i++) {
        cin >> start >> end;
        graph.push_edge(start - 1, end - 1);
    }
    int comp_edges;
    vector<int> components = graph.find_strong_components();
    int vertexes = graph.comp_edges(components);
    cout << vertexes << endl;
    for (vector<int>::iterator it = components.begin(); it != components.end(); ++it) {
        cout << *it + 1 << ' ';
    }

    //system("pause");
    return 0;
}