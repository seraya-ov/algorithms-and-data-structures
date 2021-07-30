#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    vector<vector<int>> v_lists;
    bool DFS_visit(int v, vector<char>& colors) {
        colors[v] = 'G';
        for (int u : v_lists[v]) {
            if (colors[u] == 'W') {
                if (!DFS_visit(u, colors)) {
                    return false;
                }
            }
            else if (colors[u] == 'G') {
                return false;
            }
        }
        colors[v] = 'B';
        return true;
    }
public:
    Graph(int size) : v_lists(size) {}
    void PushEdge(int i, int j) {
        v_lists[i].push_back(j);
    }

    bool findCycle() {
        int size = v_lists.size();
        vector<char>colors(size, 'W');
        for (int i = 0; i < size; i++) {
            if (colors[i] == 'W') {
                if (!DFS_visit(i, colors)) {
                    return false;
                }
            }
        }
        return true;
    }

};

int main() {
    int N;
    cin >> N;
    char c;
    Graph G(N);
    for (int i = 0; i < N - 1; i++) {
        for (int j = 1; j < N - i; j++) {
            cin >> c;
            if (c == 'R') {
                G.PushEdge(i, i + j);
            }
            else {
                G.PushEdge(i + j, i);
            }
        }
    }
    if (G.findCycle()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    // system("pause");
    return 0;
}