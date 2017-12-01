#include <string>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char* argv[]) {
	string input; cin >> input;
	int n = input.size();
	int step = n / 2;

	int64_t sum = 0;
	for (int i = 0; i < n; ++i)
		sum += (input[i] - '0') * (input[i] == input[(i + step) % n]);

	cout << sum << endl;
	return 0;
}
