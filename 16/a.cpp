#include <bits/stdc++.h>

using namespace std;

const int N = 16;
vector<char> programs(N, 0);
unordered_map<char, int> pos;

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
    for(string s; getline(fs, s, ',');) {
        istringstream iss(s);
        char op; iss >> op;
        OPS[op](iss);
    }

    for (char c : programs) cout << c;
    cout << endl;

    return 0;
}
