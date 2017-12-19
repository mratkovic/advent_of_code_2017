#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <iterator>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <cassert>

using namespace std;

vector<string> world;
const char DIR_CHANGE = '+';
const char START_CHAR = '|';

// down, right, up, left
const vector<pair<int, int>> DIRECTIONS{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const vector<char> DIRECTIONS_CHARS{'|', '-', '|', '-'};

inline bool letter(char c) {
	return c >= 'A' && c <= 'Z'; 
}
inline bool out_of_bounds(int x, int y) { 
	return y < 0 || y >= world.size() || x < 0 || y >= world[y].size();
}
inline bool is_forbidden(int old_dir, int new_dir) {
	return new_dir == (old_dir + 2) % DIRECTIONS.size();
}

int get_direction(int y, int x, int old_dir) {
	for (int d = 0; d < DIRECTIONS.size(); ++d) {
		int nx = x + DIRECTIONS[d].first;
		int ny = y + DIRECTIONS[d].second;
		int dir_c = DIRECTIONS_CHARS[d];

		if (out_of_bounds(nx, ny) || is_forbidden(old_dir, d)) continue;
		if (world[ny][nx] == dir_c || letter(world[ny][nx])) return d;
	}
	assert(false);
	return 0;
}

int main(int argc, char* argv[]) {	
	for (string s; getline(cin, s); )  world.emplace_back(s);
	
	int direction{0}, steps{0};
	int y{0}, x{int(world[0].find(START_CHAR))};
	ostringstream oss;

	while (true) {
		char c = world[y][x];
		if (letter(c)) oss << c;
		else if (c == DIR_CHANGE) {
			direction = get_direction(y, x, direction);
		} else if (c == ' ') {
			break;
		}
		++steps;
		x += DIRECTIONS[direction].first;
		y += DIRECTIONS[direction].second;
	}
	cout << oss.str() << endl;
	cout << steps << endl;
}
