#include <bits/stdc++.h>

using namespace std;

int knot_hash_ones(string s) {
    vector<int> num(256);
    iota(num.begin(), num.end(), 0);
    int step = 0, current_pos = 0;

    istringstream iss(s);
    vector<int> lens;
    lens.insert(lens.end(), istream_iterator<char>(iss), istream_iterator<char>());
    lens.insert(lens.end(), {17, 31, 73, 47, 23});

    for(int it = 0; it < 64; ++it) {
        for(int l : lens) {
            reverse(num.begin(), num.begin() + l);
            int move = (l + step++) % num.size();
            current_pos = (current_pos + move) % num.size();
            rotate(num.begin(), num.begin() + move, num.end());
        }
    }
    rotate(num.begin(), num.begin() + num.size() - current_pos, num.end());
    int sum = 0;
    for (auto b = num.begin(); b != num.end(); b += 16) {
        int x = accumulate(b, b + 16, 0, bit_xor<void>());
        sum += bitset<8>(x).count();
    }
    return sum;
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    string key; fs >> key;

    int ans = 0;
    for (int i = 0; i < 128; ++i) {
        ans += knot_hash_ones(key + "-" + to_string(i));
    }
    cout << ans << endl;
    return 0;
}
