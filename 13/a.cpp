#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <iterator>
#include <fstream>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
	int ans = 0;

	for (string s; getline(cin, s);)  {
		int i, h; char skip; 
		istringstream(s) >> i >> skip >> h;
		int len = 2 * (h - 1), offset = i % len;
		int pos = offset < h ? offset : len - offset;
		ans += pos ? 0 : i*h;
	}
	cout << ans << endl;
}

