#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> prefix_function(const string& s, int len) {
    vector<int> p(s.size(), 0);
    vector<int> answer;
    for (int i = 1; i < p.size(); ++i) {
        int t = p[i - 1];
        while (t > 0 && s[t] != s[i]) {
            t = p[t - 1];
        }
        p[i] = (s[i] == s[t] ? t + 1 : 0);
        if (p[i] == len) {
            answer.push_back(i - len * 2);
        }
    }
    return answer;
}

int main() {
    string S, T;
    cin >> S >> T;
    string sum = T + '0' + S;
    vector<int> index = prefix_function(sum, T.size());
    for (int i = 0; i < index.size(); ++i) {
        cout << index[i] << ' ';
    }
    //system("pause");
    return 0;
}