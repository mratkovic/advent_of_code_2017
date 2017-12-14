#include <bits/stdc++.h>

using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

vector<int> knot_hash_ones(string s) {
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
    vector<int> bits;
    for (auto b = num.begin(); b != num.end(); b += 16) {
        int x = accumulate(b, b + 16, 0, bit_xor<void>());
        for (int i = 7; i >= 0; --i) {
            bool bit = x & (1<<i);
            bits.emplace_back(bit);
        }
    }
    return bits;
}
void flood_fill(int i, int j, vector<vector<int>>& board, int c) {
    board[i][j] = c;
    for (int d = 0; d < 4; ++d) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (ni < 0 || ni >= board.size() || nj < 0 || nj >= board[ni].size() || board[ni][nj] != 1)
            continue;
        flood_fill(ni, nj, board, c);
    }
}

int count_rooms(vector<vector<int>>& board) {
    int c = 0; // use negative numbers as colors (free cells are 0 or 1)
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] > 0) {
                flood_fill(i, j, board, --c);
            }
        }
    }
    return -c;
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    string key; fs >> key;

    vector<vector<int>> board;
    for (int i = 0; i < 128; ++i)
        board.emplace_back(knot_hash_ones(key + "-" + to_string(i)));

    cout << count_rooms(board) << endl;
    return 0;
}
