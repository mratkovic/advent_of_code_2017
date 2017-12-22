#include <bits/stdc++.h>
#define _ << " " <<

using namespace std;

enum state {
    clean = 0, weak = 1, infected = 2, flag = 3, tot = 4
};

inline state update(state s) {
    return state((s + 1) % state::tot);
}

struct pos {
    // up, right, down, left
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};
    int x, y, dir;

    pos(int x, int y): x(x), y(y), dir(0) {}
    pair<int, int> loc() const {
        return {x, y};
    };
    void move() {
        x += dx[dir];
        y += dy[dir];
    }
    void rotate(state s) {
        switch (s) {
            case state::clean:
                dir--;
                break;
            case state::infected:
                dir++;
                break;
            case state::weak:
                break;
            case state::flag:
                dir += 2;
                break;
            default:
                break;
        }
        dir = (dir + 4) % 4;
    }
};

struct pair_hash {
    size_t operator()(const pair<int, int> &x) const {
        return hash<int64_t>() (x.first ^ (int64_t(x.second) << 32));
    }
};

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);

    unordered_map<pair<int, int>, state, pair_hash> board;
    int n_rows = 0, n_cols = 0;
    for (string line; getline(fs, line); ++n_rows) {
        n_cols = line.size();
        for (int j = 0; j < line.size(); ++j)
            if (line[j] == '#')
                board[{j, n_rows}] = state::infected;
    }
    pos p(n_cols/2, n_rows/2);
    uint64_t ans = 0;
    for (int it = 0; it < 10000000; ++it) {
        state s = board[p.loc()];
        state new_state = update(s);
        board[p.loc()] = new_state;
        p.rotate(s);
        p.move();

        ans += new_state == state::infected;
    }
    cout << ans << endl;
    return 0;
}
