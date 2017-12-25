#include <bits/stdc++.h>
#define _ << " " <<

using namespace std;
using action = function<void()>;

unordered_map<string, action> states;
unordered_set<int> tape;
int current_position;
string current_state;
int checksum_step;

vector<string> split(string str, char delim) {
    istringstream iss(str);
    vector<string> ret;
    for (string tmp; getline(iss, tmp, delim); ) {
        if (!tmp.empty())
            ret.emplace_back(tmp);
    }
    return ret;
}

inline string last_token(string line, bool trim_last=false) {
    auto token = split(line, ' ').back();
    return trim_last ? token.substr(0, token.size()-1) : token;
}

action parse_write_func(fstream& fs) {
    string line; getline(fs, line);
    assert(line.find("Write the value ") !=  string::npos);

    int val = stoi(last_token(line));
    return [val]() {
        if (val) tape.insert(current_position);
        else     tape.erase(current_position);
    };
}

action parse_move_func(fstream& fs) {
    string line; getline(fs, line);
    assert(line.find("Move one slot to the ") !=  string::npos);

    bool right = last_token(line) == "right.";
    return [right] { current_position += (right ? 1 : -1); };
}

action parse_change_state_func(fstream& fs) {
    string line; getline(fs, line);
    assert(line.find("Continue with state ") !=  string::npos);

    string next_state = last_token(line, true);
    return [next_state] { current_state = next_state; };
}

action parse_if_block(fstream& fs) {
    string line; getline(fs, line);
    assert(line.find("If the current value") !=  string::npos);

    auto write = parse_write_func(fs);
    auto move = parse_move_func(fs);
    auto change_state = parse_change_state_func(fs);

    return [write, move, change_state]() {
        write();
        move();
        change_state();
    };
}

action parse_state(fstream& fs) {
    action pos = parse_if_block(fs);
    action neg = parse_if_block(fs);
    
    return [pos, neg]() {
        if (tape.find(current_position) == tape.end())
            pos();
        else
            neg();
    };
}

void parse_states(fstream& fs) {
    for (string line; getline(fs, line);) {
        if (line.empty()) continue;
        assert(line.find("In state ") !=  string::npos);

        string state = last_token(line, true);
        states[state] = parse_state(fs);
    }
}

void parse_meta(fstream& fs) {
    string line; getline(fs, line);
    assert(line.find("Begin in state") !=  string::npos);
    auto tokens = split(line, ' ');
    current_state = last_token(line, true);

    getline(fs, line);
    assert(line.find("Perform a diagnostic checksum after") !=  string::npos);
    tokens = split(line, ' ');
    checksum_step = stoi(tokens[tokens.size() - 2]);
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    parse_meta(fs);
    parse_states(fs);

    for (int step = 0; step < checksum_step; ++step)
        states[current_state]();

    cout << tape.size() << endl;
    return 0;
}
