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
#include <fstream>
#include <cassert>

using namespace std;

int dx[] = {0, 1, 1, 0, -1, -1};
int dy[] = {1, 0, -1, -1, 0, 1};
int dz[] = {-1, -1, 0, 1, 1, 0};
vector<string> direction{"n", "ne", "se", "s", "sw", "nw"};

std::string strip( const std::string &s ) {
    std::string result;
    result.reserve(s.length());
    std::remove_copy_if(s.begin(),s.end(), back_inserter(result), not1(ptr_fun(isalpha)));
    return result;
}

int main(int argc, char* argv[]) {
	int x{0}, y{0}, z{0};
	int max_dist = INT32_MIN;
	
	auto distance = [&]() { return (abs(x) + abs(y) + abs(z)) / 2; };
	fstream fin("./input", fstream::in);
	for (string s; getline(fin, s, ','); ) {
		s = strip(s);
		int ix = find(direction.begin(), direction.end(), s) - direction.begin();
		assert(ix >= 0 && ix < direction.size());
		x += dx[ix];
		y += dy[ix];
		z += dz[ix];

		max_dist = max(max_dist, distance());
	}
	cout << distance() << endl;
	cout << "MAX: " << max_dist << endl;
	return 0;
}

