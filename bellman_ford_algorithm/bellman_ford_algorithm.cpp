#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from, to, w;
};
class Graph {
    int g_size;
    vector<Edge> Edges;
public:
    Graph(int s) : g_size(s) {}
    void push_edge(Edge i) {
        Edges.push_back(i);
    }

    vector<int> find_dists(int start, int max_dist) {
        vector<int> dp(g_size, max_dist);
        dp[start] = 0;
        for (int i = 0; i < g_size - 2; i++) {
            for (Edge e : Edges) {
                if (dp[e.from] + e.w < dp[e.to] && dp[e.from] < max_dist) {
                    dp[e.to] = dp[e.from] + e.w;
                }
            }
        }
        return dp;
    }

};

int main() {
    int n, m, from, to, w;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> w;
        graph.push_edge({ from - 1, to - 1, w });
    }
    vector<int> dists = graph.find_dists(0, 30000);
    int size = dists.size();
    for (int i = 0; i < size; i++) {
        cout << dists[i] << ' ';
    }
    //system("pause");
    return 0;
}