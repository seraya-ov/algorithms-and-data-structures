#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

class ChessGraph {
private:
    vector<vector<int>> chess_graph;
    vector<int> path;
    vector<int> horsedx;
    vector<int> horsedy;
public:
    ChessGraph(int size) {
        vector<int> horsedx = { 1, 2, 2, 1, -1, -2, -2, -1 };
        vector<int> horsedy = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int graph_size = size * size;
        chess_graph = vector<vector<int>>(graph_size);
        path = vector<int>(graph_size, -1);
        for (int i = 0; i < graph_size; i++) {
            int x = i / size;
            int y = i % size;
            for (int h = 0; h < 8; h++) {
                int newx = x + horsedx[h];
                int newy = y + horsedy[h];
                if (newx >= 0 && newy >= 0 && newx < size && newy < size) {
                    chess_graph[i].push_back(size * newx + newy);
                }
            }
        }
    }

    vector<int> GetShortestPaths(int A) {
        int size = chess_graph.size();
        vector<int> dist(size, -1);
        queue<int> q;
        int v;
        dist[A] = 0;
        q.push(A);
        while (!(q.empty())) {
            v = q.front();
            q.pop();
            for (int u : chess_graph[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    path[u] = v;
                    q.push(u);
                }
            }
        }
        return path;
    }
};


int main() {
    int N, x1, y1, x2, y2;
    cin >> N >> x1 >> y1 >> x2 >> y2;
    ChessGraph Chess(N);
    int start = (x1 - 1) * N + y1 - 1;
    vector<int> shortest_path = Chess.GetShortestPaths(start);
    int v = (x2 - 1) * N + y2 - 1;
    vector<int> path;
    while (v != -1) {
        path.push_back(v);
        v = shortest_path[v];
    }
    reverse(path.begin(), path.end());
    if (path[0] != start) {
        cout << -1 << endl;
    }
    else {
        cout << path.size() - 1 << endl;
        for (vector<int>::iterator i = path.begin(); i != path.end(); ++i)
            cout << *i / N + 1 << ' ' << *i % N + 1 << endl;
    }
    //system("pause");
    return 0;
}