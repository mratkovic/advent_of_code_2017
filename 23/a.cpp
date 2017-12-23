#include <bits/stdc++.h>

using namespace std;
unordered_map<string, long> reg;

inline long read_value(istringstream& iss) {
    string s; iss >> s;
    if (s.size() == 1 && s[0] >= 'a' && s[0] <= 'z') {
        long val = reg.find(s) != reg.end() ? reg[s] : 0;
        return val;
    }
    return stoi(s);
}

inline void binary_op(istringstream& iss, function<void(string,long)> f) {
    string r; iss >> r;
    f(r, read_value(iss));
}
unordered_map<string, function<int(istringstream&)>> OPS{
        {"jnz",  [](istringstream& iss)->int {
            long val = read_value(iss);
            long off = read_value(iss);
            if (val) return off;
            return 1;
        }},
        {"set",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] = v; });
            return 1;
        }},
        {"sub",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] -= v; });
            return 1;
        }},
        {"mul",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] *= v; });
            return 1;
        }},

};

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    vector<string> cmds;
    for(string s; getline(fs, s);)
        cmds.emplace_back(s);

    uint64_t ans = 0;
    for (int i = 0; i < cmds.size();) {
        istringstream iss(cmds[i]);
        string op; iss >> op;
        i += OPS[op](iss);
        ans += op == "mul";
    }
    cout << ans << endl;
    return 0;
}
