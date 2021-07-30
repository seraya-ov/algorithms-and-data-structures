#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdio>
using namespace std;
class SparseTable {
private:
    vector<vector<long long>> ST;
    vector<int> lg2;
    void build(const vector<long long>& values) {
        ST.push_back(values);
        int n = values.size();
        for (int k = 1; (1 << k) <= n; ++k) {
            ST.push_back(vector<long long>());
            for (int i = 0; i + (1 << (k - 1)) < ST[k - 1].size(); ++i) {
                ST[k].push_back(min(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]));
            }
        }
        lg2.push_back(0);
        lg2.push_back(0);
        for (int i = 2; i <= n; i++) {
            lg2.push_back(lg2[i / 2] + 1);
        }
    }
public:
    SparseTable(const vector<long long>& values) {
        build(values);
    }

    long long get_min(int l, int R) {
        if (l > R) {
            swap(R, l);
        }
        int k = lg2[R - l + 1];
        return min(ST[k][l], ST[k][R - (1 << k) + 1]);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    long long n, m, a_1, u, v;
    cin >> n >> m >> a_1 >> u >> v;
    vector<long long> values;
    values.push_back(a_1);
    for (int i = 1; i < n; i++) {
        values.push_back((23 * values[i - 1] + 21563) % 16714589);
    }
    SparseTable T(values);
    long long ans = 0;
    for (int i = 1; i < m; i++) {
        ans = T.get_min(u - 1, v - 1);
        u = (17 * u + 751 + ans + 2 * i) % n + 1;
        v = (13 * v + 593 + ans + 5 * i) % n + 1;
    }
    cout << u << ' ' << v << ' ' << T.get_min(u - 1, v - 1) << endl;
    /// system("pause");
    return 0;
}