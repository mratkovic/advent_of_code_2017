#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> v(istream_iterator<int>{cin}, {});
	map<vector<int>, int> seen;
	for (int i = 0; seen.find(v) == seen.end(); ++i) {
		seen.emplace(v, i);
		auto& max = max_element(v.begin(), v.end());
		int cnt = std::exchange(*max, 0);
		for (auto& it = ++max; cnt; cnt--, it++) {
			if (it == v.end()) it = v.begin();
			++*it;
		}
	}
	cout << seen.size() - seen[v] << endl;
	return 0;
}
