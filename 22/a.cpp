#include <bits/stdc++.h>
#define _ << " " <<

using namespace std;

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
    void rotate(bool clockwise) {
        dir += clockwise ? 1 : -1;
        dir = (dir + 4) % 4;
    }
};

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);

    set<pair<int, int>> infected;
    int n_rows = 0, n_cols = 0;
    for (string line; getline(fs, line); ++n_rows) {
        n_cols = line.size();
        for (int j = 0; j < line.size(); ++j)
            if (line[j] == '#')
                infected.emplace(make_pair(j, n_rows));
    }
    pos p(n_cols/2, n_rows/2);
    int ans = 0;
    for (int it = 0; it < 10000; ++it) {
        bool is_infected = infected.find(p.loc()) != infected.end();
        p.rotate(is_infected);
        if (!is_infected) {
            infected.emplace(p.loc());
            ++ans;
        } else
            infected.erase(p.loc());

        p.move();
    }
    cout << ans << endl;
    return 0;
}
