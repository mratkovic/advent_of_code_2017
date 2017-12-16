#include <bits/stdc++.h>

using namespace std;

const int N = 16;
vector<char> programs(N, 0);
unordered_map<char, int> pos;
unordered_set<string> seen;
vector<string> cycle;
vector<string> moves;

void update_hash() {
    for (int i = 0; i < programs.size(); ++i)
        pos[programs[i]] =  i;
}

unordered_map<char, function<void(istringstream& iss)>> OPS{
        {'s',  [](istringstream& iss) {
            int n; iss >> n;
            reverse(programs.begin(), programs.end());
            reverse(programs.begin(), programs.begin()+n);
            reverse(programs.begin()+n, programs.end());
            update_hash();
        }},
        {'x',  [](istringstream& iss) {
            char c;
            int a, b;
            iss >> a >> c >> b;
            swap(pos[programs[a]], pos[programs[b]]);
            swap(programs[a], programs[b]);

        }},
        {'p',  [](istringstream& iss) {
            char c;
            char a, b;
            iss >> a >> c >> b;
            int ia = pos[a];
            int ib = pos[b];
            swap(pos[programs[ia]], pos[programs[ib]]);
            swap(programs[ia], programs[ib]);

        }},
};


int main(int argc, char* argv[]) {
    for (int i = 0; i < N; ++i)
        programs[i] = 'a' + i;
    update_hash();

    fstream fs("./input", fstream::in);
    for (string s; getline(fs, s, ',');) moves.emplace_back(s);

    while (true) {
        stringstream ss;
        for (char c : programs) ss << c;
        string s = ss.str();
        if (seen.find(s) != seen.end()) break;
        seen.insert(s);
        cycle.emplace_back(s);

        for (string s : moves) {
            istringstream iss(s);
            char op; iss >> op;
            OPS[op](iss);
        }

    }
    int which = 1e9;
    cout << cycle[which % cycle.size()];
    return 0;
}
