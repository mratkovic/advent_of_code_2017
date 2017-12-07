#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <sstream>
#include <assert.h>

using namespace std;

unordered_map<string, int> w;
unordered_map<string, vector<string>> e;
unordered_map<string, int> in_edges;
unordered_map<string, int> total;

void dfs(string node) {
	if (e[node].size() == 0) return;
	map<int, int> cnts;
	map<int, string> who;
	int sum = 0;
	for (auto& ch : e[node]) {
		dfs(ch);
		cnts[total[ch]]++;
		who[total[ch]] = ch;
		sum += total[ch];
	}
	if (cnts.size() != 1) {
		auto cmp = [](auto&a, auto& b) { return a.second < b.second; };
		auto mini = *min_element(cnts.begin(), cnts.end(), cmp);
		auto maxi = *max_element(cnts.begin(), cnts.end(), cmp);
		int expected = maxi.first;
		int got = mini.first;
		int diff = expected - got;
		string wrong_node = who[got];
		cout << "ANS: " << w[wrong_node] + diff << endl;
		exit(0);
	}

	total[node] += sum;

}

int main(int argc, char* argv[]) {
	string s;
	for (int i = 0; getline(cin, s); ++i)  {
		vector<string> in(istream_iterator<string>{istringstream(s)}, {});
		string name = in[0];
		w.emplace(name, stoi(in[1].substr(1, in[1].size() - 2)));
		total.emplace(name, w[name]);
		vector<string> ch;
		transform(in.begin() + min(int(in.size()), 3), in.end(), back_inserter(ch), [](auto& s) {
			if (s.back() == ',') return s.substr(0, s.size() - 1);
			return s;
		});
		e.emplace(name, ch);
		in_edges[name] = max(in_edges[name], 0);
		for_each(ch.begin(), ch.end(), [](auto& child) { in_edges[child]++; });
	}
	auto& ans = *min_element(in_edges.begin(), in_edges.end(), [](auto&a, auto& b) { return a.second < b.second; });
	assert(ans.second == 0);
	string root = ans.first;
	dfs(root);
	return 0;
}
