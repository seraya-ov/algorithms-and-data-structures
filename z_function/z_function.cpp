#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> z_function(const string& s) {
    int size = s.size();
    vector<int> z(size, 0);
    z[0] = size;
    for (int i = 1, l = 0, r = 0; i < size; ++i) {
        z[i] = max(0, min(r - i, z[i - l]));
        while (i + z[i] < size && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    string S;
    cin >> S;
    vector<int> pi = z_function(S);
    int size = pi.size();
    for (int i = 0; i < size; ++i) {
        cout << pi[i] << ' ';
    }
    //system("pause");
    return 0;
}