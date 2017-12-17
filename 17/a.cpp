#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int step; cin >> step;

    list<int> l{0};
    int pos = 0;
    int next_val = 0;
    for (int i = 1; i <= 2017; ++i) {
        pos = (pos + step) % l.size();
        auto it = l.begin();
        for (int j = 0; j < pos; ++j, ++it){}
        l.insert(++it, i);
        ++pos;
        next_val = *it;
    }
    cout << next_val << endl;
    return 0;
}
