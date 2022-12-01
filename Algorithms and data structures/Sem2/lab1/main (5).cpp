#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string shablon, s;
    getline(cin, shablon, '\n');
    getline(cin, s, '\n');
    vector<vector<bool> > d(shablon.size() + 1);
    if (shablon.size() == 0) {
        if (s.size() == 0) {
            cout << "YES";
            return 0;
        } else {
            cout << "NO";
            return 0;
        }
    }
    if (s.size() == 0) {
        for (unsigned int i = 0; i < shablon.size(); i++) {
            if (shablon[i] != '*') {
                cout << "NO";
                return 0;
            }
        }
        cout << "YES";
        return 0;
    }
    vector<bool> a(s.size() + 1, false);
    d[0] = a;
    d[0][0] = true;
    for (unsigned int i = 1; i < shablon.size() + 1; i++) {
        d[i].resize(s.size() + 1);
        if (shablon[i - 1] == '*') {
            d[i][0] = d[i - 1][0];
            for (unsigned int j = 1; j < s.size() + 1; j++) {
                d[i][j] = d[i - 1][j] || d[i][j - 1];
            }
        } else {
            d[i][0] = false;
            for (unsigned int j = 1; j < s.size() + 1; j++) {
                if (shablon[i - 1] == s[j - 1] || shablon[i - 1] == '?') {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    d[i][j] = false;
                }
            }
        }
    }
    if (d[shablon.size()][s.size()]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
