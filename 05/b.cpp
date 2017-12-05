#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> v(istream_iterator<int>{cin}, {});
	int ans{0}, n{int(v.size())};
	for (int pos = 0; pos < n; ) {
		int offset = v[pos];
		v[pos] += v[pos] >= 3 ? -1 : 1;
		pos += offset;
		ans++;
	}
	cout << ans << endl;
	return 0;
}
