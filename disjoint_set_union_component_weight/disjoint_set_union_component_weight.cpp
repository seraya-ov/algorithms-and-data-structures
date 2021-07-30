#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    vector<int> f;
    vector<int> Rank;
    vector<int> weights;
public:
    DSU(int size) : Rank(size, 0), weights(size, 0) {
        for (int i = 0; i < size; i++) {
            f.push_back(i);
        }
    }

    int find_set(int dude) {
        if (f[dude] == dude) {
            return dude;
        }
        else {
            return f[dude] = find_set(f[dude]);
        }
    }
    void union_s(int a, int b, int w) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (Rank[a] > Rank[b]) {
                swap(a, b);
            }
            f[a] = b;
            weights[b] += weights[a];
            weights[b] += w;
            if (Rank[a] == Rank[b]) {
                Rank[b]++;
            }
        }
        else {
            weights[b] += w;
        }
    }
    int comp_weight(int i) {
        return weights[i];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int x, y, w, m, n, comand, cur_comp;
    cin >> n >> m;
    DSU graph(n);
    for (int i = 0; i < m; i++) {
        cin >> comand;
        if (comand == 1) {
            cin >> x >> y >> w;
            graph.union_s(x - 1, y - 1, w);
        }
        else if (comand == 2) {
            cin >> x;
            cur_comp = graph.find_set(x - 1);
            cout << graph.comp_weight(cur_comp) << endl;
        }
    }
    //system("pause");
    return 0;
}