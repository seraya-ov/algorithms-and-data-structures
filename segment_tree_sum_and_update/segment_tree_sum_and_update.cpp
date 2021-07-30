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
    void build(int v, int l, int r, const vector<long long>& init) {
        if (l == r - 1) {
            tree[v] = init[l];
        }
        else {
            build(v * 2 + 1, l, (l + r) / 2, init);
            build(v * 2 + 2, (l + r) / 2, r, init);
            tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
        }
    }

    long long query(int v, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) {
            return 0;
        }
        else if (ql <= l && r <= qr) {
            return tree[v];
        }
        else {
            return (query(2 * v + 1, l, (l + r) / 2, ql, qr) + query(2 * v + 2, (l + r) / 2, r, ql, qr));
        }
    }

    void edit(int v, int l, int r, int idx, long long value) {
        if (l == r - 1) {
            tree[v] = value;
        }
        else {
            if (idx < (l + r) / 2) {
                edit(2 * v + 1, l, (l + r) / 2, idx, value);
            }
            else {
                edit(2 * v + 2, (l + r) / 2, r, idx, value);
            }
            tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
        }
    }
public:
    SegmentTree(const vector<long long>& init) : tree(init.size() * 4), n(init.size()) {
        build(0, 0, n, init);
    }

    long long sum(int l, int r) {
        return query(0, 0, n, l, r + 1);
    }

    void edit(int idx, long long value) {
        edit(0, 0, n, idx, value);
    }
};

int main() {
    int N, M, left, right, idx;
    long long value;
    char comand;
    cin >> N;
    vector<long long> init(N);
    for (int i = 0; i < N; i++) {
        cin >> init[i];
    }
    SegmentTree tree(init);
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> comand;
        if (comand == 's') {
            cin >> left >> right;
            cout << tree.sum(left - 1, right - 1) << ' ';
        }
        else if (comand == 'u') {
            cin >> idx >> value;
            tree.edit(idx - 1, value);
        }
    }

    // system("pause");
    return 0;
}