#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int g_size;
    vector<vector<int>> graph;
    const static int infinity = 1000000000;
public:
    Graph(int s) : g_size(s), graph(s, vector<int>(s, infinity)) {}
    void push_edge(int i, int j, int w) {
        graph[i][j] = w;
    }

    int findTheShortestWay(int from, int to) {
        vector<vector<int>> dp = graph;
        for (int k = 0; k < g_size; k++) {
            for (int i = 0; i < g_size; i++) {
                for (int j = 0; j < g_size; j++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        if (dp[from][to] == infinity) {
            return -1;
        }
        return dp[from][to];
    }

};

int main() {
    int n, from, to, w;
    cin >> n >> from >> to;
    Graph graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w;
            if (w != -1) {
                graph.push_edge(i, j, w);
            }
        }
    }
    cout << graph.findTheShortestWay(from - 1, to - 1) << endl;
    // system("pause");
    return 0;
}