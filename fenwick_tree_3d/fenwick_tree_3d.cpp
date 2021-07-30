#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<vector<vector<int>>> f;
    int size;
public:
    FenwickTree(int n) : size(n), f(n, vector<vector<int>>(n, vector<int>(n, 0))) {}

    int sumOnPrefix(int x, int y, int z) {
        int result = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                    result += f[i][j][k];
                }
            }
        }
        return result;
    }

    void add(int x, int y, int z, int s) {
        for (int i = x; i < size; i = (i | (i + 1))) {
            for (int j = y; j < size; j = (j | (j + 1))) {
                for (int k = z; k < size; k = (k | (k + 1))) {
                    f[i][j][k] += s;
                }
            }
        }
    }
};


int main() {
    int n, x1, y1, z1, x2, y2, z2, k, comand;
    cin >> n;
    FenwickTree tree(n);
    for (bool i = true; i;) {
        cin >> comand;
        if (comand == 1) {
            cin >> x1 >> y1 >> z1 >> k;
            tree.add(x1, y1, z1, k);
        }
        else if (comand == 2) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            int answer = tree.sumOnPrefix(x2, y2, z2) - tree.sumOnPrefix(x2, y2, z1 - 1) - tree.sumOnPrefix(x2, y1 - 1, z2) - tree.sumOnPrefix(x1 - 1, y2, z2) + tree.sumOnPrefix(x1 - 1, y1 - 1, z2) + tree.sumOnPrefix(x1 - 1, y2, z1 - 1) + tree.sumOnPrefix(x2, y1 - 1, z1 - 1) - tree.sumOnPrefix(x1 - 1, y1 - 1, z1 - 1);
            cout << answer << endl;
        }
        else if (comand == 3) {
            i = false;
        }
    }

    //system("pause");
    return 0;
}