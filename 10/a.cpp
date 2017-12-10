#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <functional>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> num(256);
	iota(num.begin(), num.end(), 0);
	int step = 0, current_pos = 0;
	for (string s; getline(cin, s, ','); ) {
		int l = stoi(s);
		reverse(num.begin(), num.begin() + l);
		int move = (l + step++) % num.size();
		current_pos = (current_pos + move) % num.size();
		rotate(num.begin(), num.begin() + move, num.end());
	}
	rotate(num.begin(), num.begin() + num.size() - current_pos, num.end());
	cout << num[0] << ", " << num[1] << endl;
	cout << num[0] * num[1] << endl;
	return 0;
}
