#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<vector<int>> f;
    int xsize, ysize;
public:
    FenwickTree(int x, int y) : xsize(x), ysize(y), f(x, vector<int>(y, 0)) {
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                add(i, j, 0);
            }
        }
    }

    int sumOnPrefix(int x, int y) {
        int result = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                result += f[i][j];
            }
        }
        return result;
    }

    void add(int x, int y, int k) {
        for (int i = x; i < xsize; i = (i | (i + 1))) {
            for (int j = y; j < ysize; j = (j | (j + 1))) {
                f[i][j] += k;
            }
        }
    }
};


int main() {
    int x, y, n, x1, y1, x2, y2, k, comand;
    cin >> x >> y;
    FenwickTree tree(x, y);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> comand;
        if (comand == 1) {
            cin >> x1 >> y1 >> k;
            x1--;
            y1--;
            tree.add(x1, y1, k);
        }
        else if (comand == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            x2--;
            y1--;
            y2--;
            int answer = tree.sumOnPrefix(x2, y2) - tree.sumOnPrefix(x1 - 1, y2) - tree.sumOnPrefix(x2, y1 - 1) + tree.sumOnPrefix(x1 - 1, y1 - 1);
            cout << answer << endl;
        }
    }

    //system("pause");
    return 0;
}