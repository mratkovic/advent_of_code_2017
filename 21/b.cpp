#include <bits/stdc++.h>
#define _ << " " <<

using namespace std;

string flip_lr(const string& in) {
    int size = sqrt(in.size());
    string out(in);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size/2; ++j)
            swap(out[i*size + j], out[i*size + size - 1 - j]);
    return out;
}
string rotate(const string& in) {
    int size = sqrt(in.size());
    string out(in);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            out[j*size + i] = in[(size - 1- i) * size + j];
    return out;
}

unordered_set<string> all_combinations(const string& in) {
    unordered_set<string> uniq;
    uniq.insert(in);
    string prev = in;
    for (int i = 0; i < 4; ++i) {
        string s = rotate(prev);
        uniq.insert(s);
        uniq.insert(flip_lr(s));
        prev = s;
    }
    return uniq;
}

vector<string> split_pattern(const string& in) {
    const int sz = sqrt(in.size());
    if (sz <= 3)
        return {in};

    const int step = sz % 2 == 0 ? 2 : 3;
    vector<string> ret;
    for (int sx = 0; sx < sz; sx += step) {
        for (int sy = 0; sy < sz; sy += step) {
            string s(pow(step, 2), ' ');
            for (int i = 0; i < step; ++i)
                for (int j = 0; j < step; ++j)
                    s[i * step + j] = in[(sx + i) * sz + sy + j];
            ret.emplace_back(s);
        }
    }
    return ret;
}

string union_patterns(const vector<string>& in) {
    if (in.size() == 1)
        return in.front();

    const int small_sz = sqrt(in[0].size());
    const int row_grids = sqrt(in.size());
    const int sz = row_grids * small_sz;
    string ret(sz * sz, ' ');

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            int idx = i/small_sz * row_grids + j/small_sz;
            ret[i*sz + j] = in[idx][(i%small_sz) * small_sz + (j%small_sz)];
        }
    }
    return ret;
}

inline long cnt_on(const string& s) {
    return std::count(s.begin(), s.end(), '#');
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);

    map<string, string> rules;
    auto remove_sep = [](string& s) {
        s.erase(std::remove(s.begin(), s.end(), '/'), s.end());
    };
    for (string line; getline(fs, line);) {
        string from, to, skip;
        istringstream iss(line);
        iss >> from >> skip >> to;
        remove_sep(from); remove_sep(to);
        for (const string& left : all_combinations(from)){
            assert(rules.find(left) == rules.end());
            rules[left] = to;
        }
    }
    string grid = ".#./..#/###";
    remove_sep(grid);
    for (int it = 0; it < 18; ++it) {
        auto splited = split_pattern(grid);
        vector<string> to(splited.size());
        transform(splited.begin(), splited.end(), to.begin(), [&rules](auto& s) { return rules[s]; });
        grid = union_patterns(to);
        cout << "iter: " << it << "; cnt: " << cnt_on(grid) << endl;
    }
    return 0;
}
