#include <bits/stdc++.h>

using namespace std;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const int DIR = 4;

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    int target; fs >> target;

    int x = 0, y = 0;
    for (int i = 0, step = 1; step < target; ++i) {
        int move_by = (i/2 + 1);     // 1,1,2,2,3,3..... movements
        for (int j = 0; j < move_by && step < target; ++j, ++step) {
            x += dx[i % DIR];
            y += dy[i % DIR];
        }
    }
    cout << abs(x) + abs(y) << endl;
    return 0;
}
