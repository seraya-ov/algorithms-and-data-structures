#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class Graph {
    vector<vector<pair<int, int>>> graph;
public:
    Graph(int size) : graph(size) {}

    void PushEdge(int i, int j, int w) {
        graph[i].push_back({ j, w });
    }

    int findMSTweight() {
        int n = graph.size();
        vector<int> d(n, 1000000000);
        vector<bool> used(n, false);
        priority_queue<pair<int, int>> q;
        q.push({ 0,0 });
        d[0] = 0;
        int result = 0;
        while (!q.empty()) {
            int v = q.top().second;
            q.pop();
            while (used[v] && !q.empty()) {
                v = q.top().second;
                q.pop();
            }
            if (used[v] && q.empty()) break;
            used[v] = true;
            result += d[v];
            for (pair<int, int> u : graph[v]) {
                if (d[u.first] > u.second) {
                    d[u.first] = u.second;
                    q.push({ -1 * u.second, u.first });
                }
            }
        }
        return result;
    }
};

int main() {
    int n, m, t1, t2, w;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> t1 >> t2 >> w;
        graph.PushEdge(t1 - 1, t2 - 1, w);
        graph.PushEdge(t2 - 1, t1 - 1, w);
    }
    cout << graph.findMSTweight() << endl;
    //system("pause");
    return 0;
}