#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class DSU {
    vector<int> f;
    vector<int> Rank;
    int set_number;
public:
    DSU(int size) : Rank(size, 0), set_number(size) {
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
    int union_s(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            set_number--;
            if (Rank[a] > Rank[b]) {
                swap(a, b);
            }
            f[a] = b;
            if (Rank[a] == Rank[b]) {
                Rank[b]++;
            }
        }
        return set_number;
    }
};


int main() {
    int n, m, x, y;
    cin >> n >> m;
    int bridges_num = m;
    DSU island_map(n);
    int set_number = n;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        if (set_number > 1) {
            set_number = island_map.union_s(x, y);
            if (set_number == 1) {
                bridges_num = i + 1;
            }
        }
    }
    cout << bridges_num << endl;
    // system("pause");
    return 0;
}