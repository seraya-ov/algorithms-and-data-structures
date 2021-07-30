#include <iostream>
#include <vector>
using namespace std;
class Graph {
    vector<vector<int>> v_lists;
    vector<vector<int>> comp_lists;
    vector<int> components;
public:
    Graph(int size) : v_lists(size) {}
    void PushEdge(int v, int u) {
        v_lists[v].push_back(u);
        v_lists[u].push_back(v);
    }
    void DFSforComponent(int v, int comp_num) {
        comp_lists[comp_num].push_back(v);
        components[v] = comp_num;
        for (int u : v_lists[v]) {
            if (components[u] == -1) {
                DFSforComponent(u, comp_num);
            }
        }
    }

    vector<vector<int>> findComponents() {
        int comp_num = 0;
        int size = v_lists.size();
        components = vector<int>(size, -1);
        for (int i = 0; i < size; i++) {
            if (components[i] == -1) {
                comp_lists.push_back(vector<int>());
                DFSforComponent(i, comp_num++);
            }
        }
        return comp_lists;
    }
};

int main() {
    int N, M, i, j;
    vector<vector<int>> comp_list;
    cin >> N >> M;
    Graph graph(N);
    for (int t = 0; t < M; t++) {
        cin >> i >> j;
        graph.PushEdge(i - 1, j - 1);
    }
    comp_list = graph.findComponents();
    cout << comp_list.size() << endl;
    for (vector<int> v : comp_list) {
        cout << v.size() << endl;
        for (int u : v) {
            cout << u + 1 << ' ';
        }
        cout << endl;
    }

    //system("pause");
    return 0;
}