#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdio>
using namespace std;

class SegmentTree {
private:
    vector<long long> tree;
    int n;

    long long query(int v, int l, int r, int i, long long sum) {
        if (v == i) {
            return sum + tree[v];
        }
        else {
            sum += tree[v];
            if (i + 1 - n <= (l + r) / 2) {
                query(2 * v + 1, l, (l + r) / 2, i, sum);
            }
            else {
                query(2 * v + 2, (l + r) / 2 + 1, r, i, sum);
            }
        }
    }

    void edit(int v, int ql, int qr, int l, int r, long long val) {
        if (l <= r) {
            if (ql == l && qr == r) {
                tree[v] += val;
            }
            else {
                edit(2 * v + 1, ql, (ql + qr) / 2, l, min((ql + qr) / 2, r), val);
                edit(2 * v + 2, (ql + qr) / 2 + 1, qr, max((ql + qr) / 2 + 1, l), r, val);
            }
        }
    }

public:
    SegmentTree(const vector<long long>& init) : tree(init.size()* int(log2(init.size())), 0), n(init.size()) {
        for (int i = 0; i < n; i++) {
            tree[n + i - 1] = init[i];
        }
    }

    long long query(int index) {
        return query(0, 0, n - 1, n + index - 1, 0);
    }

    void edit(int left, int right, long long value) {
        edit(0, 0, n - 1, left, right, value);
    }

};

int main() {
    int N, M, l, r, value;
    char comand;
    cin >> N;
    vector<long long> init(N);
    for (int i = 0; i < N; i++) {
        cin >> init[i];
    }
    int l2 = 0;
    while ((1 << l2) < init.size()) {
        l2++;
    };
    init.resize((1 << l2), 0);
    SegmentTree tree(init);
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> comand;
        if (comand == 'g') {
            cin >> value;
            cout << tree.query(value - 1) << endl;
        }
        else if (comand == 'a') {
            cin >> l >> r >> value;
            tree.edit(l - 1, r - 1, value);
        }

    }
    //system("pause");
    return 0;
}