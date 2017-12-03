#include <bits/stdc++.h>

using namespace std;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const int DIR = 4;

int neigh_sum(int x, int y, map<pair<int, int>, int>& board) {
    int sum = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x+dx, ny = y + dy;
            sum += board[{nx, ny}];
        }
    }
    return sum;
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    int target; fs >> target;
    map<pair<int, int>, int> board;
    board[{0, 0}] = 1;

    int x = 0, y = 0;
    for (int i = 0; true; ++i) {
        int move_by = (i/2 + 1);     // 1,1,2,2,3,3..... movements
        for (int j = 0; j < move_by; ++j) {
            x += dx[i % DIR]; y += dy[i % DIR];

            int sum = neigh_sum(x, y, board);
            if (sum > target) {
                cout << sum << endl;
                exit(0);
            }
            // cout << x << " " << y << " " <<sum << endl;
            board[{x,y}] = sum ;
        }
    }
    return 0;
}
