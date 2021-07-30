#include <iostream>
#include <vector>
using namespace std;
class Graph {
    vector<vector<int>> v_lists;
public:
    Graph(int size) : v_lists(size) {}
    void PushEdge(int v, int u) {
        v_lists[v].push_back(u);
    }
    bool DFS_visit(int v, vector<char>& colors, vector<int>& cycle) {
        colors[v] = 'G';
        cycle.push_back(v);
        for (int u : v_lists[v]) {
            if (colors[u] == 'W') {
                if (!DFS_visit(u, colors, cycle)) {
                    return false;
                }
            }
            else if (colors[u] == 'G') {
                cycle.push_back(u);
                return false;
            }
        }
        colors[v] = 'B';
        cycle.pop_back();
        return true;
    }

    bool findCycle(vector<int>& cycle) {
        int size = v_lists.size();
        vector<char>colors(size, 'W');
        for (int i = 0; i < size; i++) {
            if (colors[i] == 'W') {
                cycle.clear();
                if (!DFS_visit(i, colors, cycle)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    int N, M, i, j;
    cin >> N >> M;
    Graph graph(N);
    for (int t = 0; t < M; t++) {
        cin >> i >> j;
        graph.PushEdge(i - 1, j - 1);
    }
    vector<int> cycle;
    if (graph.findCycle(cycle)) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
        int size = cycle.size();
        int i = size - 2;
        for (i; i >= 0 && cycle[i] != cycle[size - 1]; i--) {}
        for (i; i < size - 1; i++) {
            cout << cycle[i] + 1 << ' ';
        }
    }

    //system("pause");
    return 0;
}