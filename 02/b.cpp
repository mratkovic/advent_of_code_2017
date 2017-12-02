#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int ans = 0;
    fstream fs("./input", fstream::in);
    for (string s; getline(fs, s);) {
        istringstream iss(s);
        vector<int> v(istream_iterator<int>(iss), {});
        for (int i = 0; i < v.size(); ++i)
            for (int j = i+1; j < v.size(); ++j) {
                int a = min(v[i], v[j]);
                int b = max(v[i], v[j]);
                ans += (b % a == 0) * b/a;
            }
    }
    cout << ans << endl;
    return 0;
}
