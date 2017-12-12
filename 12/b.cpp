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
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

unordered_map <int, vector<int>> graph;
unordered_map<int, int> color;


void color_graph(int node, int c) {
	if (color.find(node) != color.end())
		return;

	color[node] = c;
	for (int next : graph[node]) {
		color_graph(next, c);
	}
}
int main(int argc, char* argv[]) {
	for (string s; getline(cin, s);)  {
		vector<string> in(istream_iterator<string>{istringstream(s)}, {});
		vector<int> ch;
		transform(in.begin() + min(int(in.size()), 2), in.end(), back_inserter(ch), [](auto& s) {
			if (s.back() == ',') s = s.substr(0, s.size() - 1);
			return stoi(s);
		});
		int p = stoi(in[0]);
		graph[p].emplace_back(p);
		for_each(ch.begin(), ch.end(), [&p](int c) {
			graph[p].emplace_back(c);
			graph[c].emplace_back(p);
		});
	}
	int c = 0;
	for (auto& n : graph) {
		int node = n.first;
		if (color.find(node) == color.end()) {
			color_graph(node, c++);
		}
	}
	int ans0 = accumulate(color.begin(), color.end(), 0, [](int r, pair<int, int> c){
		return r + (c.second == color[0]);
	});
	cout << ans0 << endl;
	cout << c << endl;

}
