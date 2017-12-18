#include <bits/stdc++.h>

using namespace std;
unordered_map<string, long> reg;
int last_played = 0;
int last_recv = -1;

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
    //cout << "\t " << r << " = " << reg[r] << endl;
}
unordered_map<string, function<int(istringstream&)>> OPS{
        {"snd",  [](istringstream& iss)->int {
            last_played = read_value(iss);
            return 1;
        }},
        {"rcv",  [](istringstream& iss)->int {
            long val = read_value(iss);
            if (val) last_recv = last_played;
            return 1;
        }},
        {"jgz",  [](istringstream& iss)->int {
            long val = read_value(iss);
            long off = read_value(iss);
            if (val) return off;
            return 1;
        }},
        {"set",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] = v; });
            return 1;
        }},
        {"add",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] += v; });
            return 1;
        }},
        {"mul",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] *= v; });
            return 1;
        }},
        {"mod",  [](istringstream& iss)->int {
            binary_op(iss, [](string s, long v) { reg[s] %= v; });
            return 1;
        }},

};

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    vector<string> cmds;
    for(string s; getline(fs, s);)
        cmds.emplace_back(s);

    for (int i = 0; i < cmds.size();) {
        //cout << i << "; " << cmds[i] << endl;
        istringstream iss(cmds[i]);
        string op; iss >> op;
        i += OPS[op](iss);
        if (last_recv != -1) {
            break;
        }
    }
    cout << last_recv << endl;
    return 0;
}
