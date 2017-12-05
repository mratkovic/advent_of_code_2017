#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> v(istream_iterator<int>{cin}, {});
	int ans{0}, n{int(v.size())};
	for (int pos = 0; pos < n; ) {
		pos += (v[pos]++);
		ans++;
	}
	cout << ans << endl;
	return 0;
}
