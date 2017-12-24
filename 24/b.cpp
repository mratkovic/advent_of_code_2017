#include <bits/stdc++.h>
#define _ << " " <<

using namespace std;

struct component {
    int x, y;
    bool used;
    int strength() const { return x + y;}
};

vector<component> components;
int max_strength;
int max_len;

void dfs(uint8_t port, int strength, int len) {
    if (len >= max_len) {
        max_len = len;
        max_strength = len > max_len ? strength : max(max_strength, strength);
    }

    for (auto& c : components) {
        if (!c.used && (c.x == port || c.y == port)) {
            uint8_t output = c.x == port ? c.y : c.x;
            c.used = true;
            dfs(output, strength + c.strength(), len+1);
            c.used = false;
        }
    }
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    for(string s; getline(fs, s);) {
        int in, out;
        char skip;
        istringstream(s) >> in >> skip >> out;
        component c {in, out, false};
        components.emplace_back(c);
    }
    dfs(0, 0, 0);
    cout << max_strength << endl;
    return 0;
}
