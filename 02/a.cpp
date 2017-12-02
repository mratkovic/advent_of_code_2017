#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int ans = 0;
    fstream fs("./input", fstream::in);
    for (string s; getline(fs, s);) {
        istringstream iss(s);
        vector<int> v(istream_iterator<int>(iss), {});
        auto res = minmax_element(v.begin(), v.end());
        ans += *res.second - *res.first;
    }
    cout << ans << endl;
    return 0;
}
