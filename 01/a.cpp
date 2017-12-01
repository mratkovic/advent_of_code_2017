#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	fstream fs("./input", fstream::in);
	string input; fs >> input;
	int n = input.size();

	int64_t sum = 0;
	for (int i = 0; i < n; ++i)
		sum += (input[i] - '0') * (input[i] == input[(i + 1) % n]);

	cout << sum << endl;
	return 0;
}
