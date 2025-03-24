#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("levenshtein.in");
    ofstream cout("levenshtein.out");
    string s1, s2;
    cin >> s1 >> s2;
    vector<vector<int> > dist(s1.size() + 1);
    vector<int> first_line(s2.size() + 1);
    for (unsigned int i = 0; i < s2.size() + 1; i++) {
        first_line[i] = i;
    }
    dist[0] = first_line;
    for (unsigned int i = 1; i < s1.size() + 1; i++) {
        dist[i].resize(s2.size() + 1);
        dist[i][0] = i;
        for (unsigned int j = 1; j < s2.size() + 1; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dist[i][j] = min(dist[i - 1][j] + 1,
                                 min(dist[i - 1][j - 1], dist[i][j - 1] + 1));
            } else {
                dist[i][j] = min(dist[i - 1][j] + 1,
                                 min(dist[i - 1][j - 1] + 1, dist[i][j - 1] + 1));
            }
        }
    }
    cout << dist[s1.size()][s2.size()];
    return 0;
}
