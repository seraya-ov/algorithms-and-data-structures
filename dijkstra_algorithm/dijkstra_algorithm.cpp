#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <functional>
using namespace std;

class Graph {
    vector<vector<pair<int, int>>> graph;
public:
    Graph(int size) : graph(size) {}

    void PushEdge(int i, int j, int w) {
        graph[i].push_back({ j, w });
        graph[j].push_back({ i, w });
    }

    vector<int> findTheShortestPath(int s, int infinity) {
        int size = graph.size();
        priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        vector<int> dists(size, infinity);
        dists[s] = 0;
        q.push({ 0, s });
        while (!q.empty()) {
            pair<int, int> d = { -1, infinity };
            d = q.top();
            d = { d.second, d.first };
            q.pop();
            while (dists[d.first] != d.second) {
                if (q.empty()) {
                    return dists;
                }
                d = q.top();
                d = { d.second, d.first };
                q.pop();
            }
            for (pair<int, int> j : graph[d.first]) {
                if (dists[j.first] > dists[d.first] + j.second) {
                    dists[j.first] = dists[d.first] + j.second;
                    q.push({ dists[j.first], j.first });
                }
            }
        }
        return dists;
    }
};


int main() {
    int NUM, N, M, from, to, w, s, infinity = 2009000999;
    cin >> NUM;
    for (int i = 0; i < NUM; i++) {
        cin >> N >> M;
        Graph graph(N);
        for (int j = 0; j < M; j++) {
            cin >> from >> to >> w;
            graph.PushEdge(from, to, w);
        }
        cin >> s;
        vector<int> dists = graph.findTheShortestPath(s, infinity);
        for (int j : dists) {
            cout << j << ' ';
        }
        cout << endl;
    }

    //system("pause");
    return 0;
}