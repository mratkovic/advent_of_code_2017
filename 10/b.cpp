#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <functional>
#include <vector>
#include <numeric>
#include <iterator>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
	vector<int> num(256);
	iota(num.begin(), num.end(), 0);
	int step = 0, current_pos = 0;

	vector<int> lens;
	lens.insert(lens.end(), std::istream_iterator<char>{std::cin}, {});
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


	for (auto b = num.begin(); b != num.end(); b += 16) {
		int xor = accumulate(b, b + 16, 0, bit_xor<void>());
		printf("%02x", xor);
	}
	return 0;
}
