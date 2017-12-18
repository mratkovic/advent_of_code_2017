#include <bits/stdc++.h>

using namespace std;

enum ProgramState {
    WAIT, TERMINATED, OK
};

struct Program {
    unordered_map<string, long> reg;
    vector<string> cmds;
    queue<int> q;

    ProgramState state = OK;
    int send_cnt = 0;
    int i = 0;
    int id;

    function<void(int)> send_callback;

    Program(vector<string> cmds, int id): cmds(cmds), id(id) {
        reg["p"] = id;
    }

    long read_value(istringstream &iss) {
        string s;
        iss >> s;
        if (s.size() == 1 && s[0] >= 'a' && s[0] <= 'z') {
            long val = reg.find(s) != reg.end() ? reg[s] : 0;
            return val;
        }
        return stoi(s);
    }

    inline void binary_op(istringstream &iss, function<void(string, long)> f) {
        string r;
        iss >> r;
        f(r, read_value(iss));
    }

    unordered_map<string, function<int(istringstream &)>> OPS{
            {"snd", [this](istringstream &iss) -> int {
                send_callback(read_value(iss));
                send_cnt++;
                return 1;
            }},
            {"rcv", [this](istringstream &iss) -> int {
                string r; iss >> r;
                if (q.empty()) {
                    state = WAIT;
                    return 0;
                }
                reg[r] = q.front();
                q.pop();
                return 1;
            }},
            {"jgz", [this](istringstream &iss) -> int {
                long val = read_value(iss);
                long off = read_value(iss);
                if (val > 0) return off;
                return 1;
            }},
            {"set", [this](istringstream &iss) -> int {
                binary_op(iss, [this](string s, long v) { reg[s] = v; });
                return 1;
            }},
            {"add", [this](istringstream &iss) -> int {
                binary_op(iss, [this](string s, long v) { reg[s] += v; });
                return 1;
            }},
            {"mul", [this](istringstream &iss) -> int {
                binary_op(iss, [this](string s, long v) { reg[s] *= v; });
                return 1;
            }},
            {"mod", [this](istringstream &iss) -> int {
                binary_op(iss, [this](string s, long v) { reg[s] %= v; });
                return 1;
            }},

    };
    bool can_continue() {
        return !q.empty();
    }

    ProgramState get_state() {
        return state == WAIT && can_continue() ? OK : state;
    }

    void print_reg() {
        for(auto c : reg) {
            cout << "\t" << c.first << ": " << c.second << endl;
        }
        cout << endl;
    }
    void run() {
        state = OK;
        while(i < cmds.size()) {
            istringstream iss(cmds[i]);
            string op; iss >> op;
            i += OPS[op](iss);
            if (state == WAIT)
                return;
        }
        state = TERMINATED;
    }
};

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    vector<string> cmds;
    for(string s; getline(fs, s);)
        cmds.emplace_back(s);

    auto p1 = Program(cmds, 0);
    auto p2 = Program(cmds, 1);
    p1.send_callback = [&p2](int x) { p2.q.push(x); };
    p2.send_callback = [&p1](int x) { p1.q.push(x); };

    auto isDeadlock = [&p1, &p2]() {
        // both terminated or stuck waiting
        return p1.get_state() == p2.get_state() && (p1.get_state() == WAIT || p1.get_state() == TERMINATED);
    };
    while(!isDeadlock()) {
        p1.run();
        p2.run();
    }

    cout << p2.send_cnt << endl;
    return 0;
}
