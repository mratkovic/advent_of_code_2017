#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> v(istream_iterator<int>{cin}, {});
	set<vector<int>> seen;
	while (seen.find(v) == seen.end()) {
		seen.emplace(v);
		auto& max = max_element(v.begin(), v.end());
		int cnt = std::exchange(*max, 0);
		for (auto& it = ++max; cnt; cnt--, it++) {
			if (it == v.end()) it = v.begin();
			++*it;
		}
	}
	cout << seen.size() << endl;
	return 0;
}
