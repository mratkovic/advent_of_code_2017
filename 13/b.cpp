#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <iterator>
#include <fstream>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
	unordered_map<int, int> board;
	int i, h; char skip; 
	for (string s; getline(cin, s);)  {
		istringstream(s) >> i >> skip >> h;
		board[i] = h;
	}

	auto is_ok = [&board, &i, &h](int t) {
		return all_of(board.begin(), board.end(), [&](auto& e) {
			tie(i, h) = e;
			i += t;
			int len = 2 * (h - 1), offset = i % len;
			int pos = offset < h ? offset : len - offset;
			return pos != 0;
		});
	};

	int t = 0;
	for (t = 0; !is_ok(t); ++t) {}
	std::cout << t << endl;
}

