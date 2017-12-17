#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int step; cin >> step;
    int pos = 0;
    int ans = -1;
    for (int i = 1; i <= 50000000; ++i) {
        pos = (pos + step + 1) % i;
        if (pos == 0) ans = i;
    }
    cout << ans << endl;
    return 0;
}
