#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
	int ans{0};
	for (string s; getline(cin, s);) {
		vector<string> words;
		unordered_set<string> unique;
		for_each(istream_iterator<string>{istringstream(s)}, {}, [&words, &unique](const string& s) {
			words.emplace_back(s);
			unique.insert(s);
		});
		ans += words.size() == unique.size();
	}
	cout << ans << endl;
	return 0;
}
