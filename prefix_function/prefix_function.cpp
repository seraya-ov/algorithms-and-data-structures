#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> prefix_function(const string& s) {
    vector<int> p(s.size(), 0);
    for (int i = 1; i < p.size(); ++i) {
        int t = p[i - 1];
        while (t > 0 && s[t] != s[i]) {
            t = p[t - 1];
        }
        p[i] = (s[i] == s[t] ? t + 1 : 0);
    }
    return p;
}

int main() {
    string S;
    cin >> S;
    vector<int> pi = prefix_function(S);
    for (int i = 0; i < pi.size(); ++i) {
        cout << pi[i] << ' ';
    }
    // system("pause");
    return 0;
}