#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to, w;
};
class Graph {
    int g_size;
    vector<Edge> Edges;
public:
    vector<int> negativeCycle;

    Graph(int s) : g_size(s) {}
    void push_edge(Edge i) {
        Edges.push_back(i);
    }

    bool NegativeCycle() {
        int infinity = -1000000000;
        vector<int> dists(g_size);
        vector<int> path(g_size, -1);
        int CyclePoint;
        for (int i = 0; i < g_size; i++) {
            CyclePoint = -1;
            for (Edge e : Edges) {
                if (dists[e.to] > dists[e.from] + e.w) {
                    dists[e.to] = infinity > dists[e.from] + e.w ? infinity : dists[e.from] + e.w;
                    path[e.to] = e.from;
                    CyclePoint = e.to;
                }
            }
        }
        if (CyclePoint == -1) {
            return false;
        }
        else {
            int CyclePoint2 = CyclePoint;
            for (int i = 0; i < g_size; i++) {
                CyclePoint2 = path[CyclePoint2];
            }
            for (int CurPoint = CyclePoint2; ; CurPoint = path[CurPoint]) {
                negativeCycle.push_back(CurPoint);
                if (CurPoint == CyclePoint2 && negativeCycle.size() > 1) {
                    break;
                }
            }
            reverse(negativeCycle.begin(), negativeCycle.end());
            return true;
        }
    }

};

int main() {
    int n, w;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w;
            if (w < 100000) {
                graph.push_edge({ i, j, w });
            }
        }
    }
    if (graph.NegativeCycle()) {
        cout << "YES" << endl;
        int size = graph.negativeCycle.size();
        cout << size << endl;
        for (int i = 0; i < size; i++) {
            cout << graph.negativeCycle[i] + 1 << ' ';
        }
    }
    else {
        cout << "NO" << endl;
    }

    //system("pause");
    return 0;
}