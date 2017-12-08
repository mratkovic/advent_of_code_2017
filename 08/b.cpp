#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <functional>

using namespace std;

map<string, int> reg;
map<string, function<int(string, string)>> OPS{{
	{"inc", [](string r, string amount) { return reg[r] += stoi(amount); }},
	{"dec", [](string r, string amount) { return reg[r] -= stoi(amount); }}
}};
map<string, function<bool(string, string)>> CMP_OPS{{
	{"<", [](string r, string amount) { return reg[r] < stoi(amount); }}, 
	{"<=", [](string r, string amount) { return reg[r] <= stoi(amount); }}, 
	{">", [](string r, string amount) { return reg[r] > stoi(amount); }}, 
	{">=", [](string r, string amount) { return reg[r] >= stoi(amount); }}, 
	{"==", [](string r, string amount) { return reg[r] == stoi(amount); }}, 
	{"!=", [](string r, string amount) { return reg[r] != stoi(amount); }}, 
}};

int main(int argc, char* argv[]) {
	int max_ever = INT32_MIN;
	for (string s; getline(cin, s);)  {
		string r1, op, amount, if_s, r2, cmp_str, val;
		istringstream(s) >> r1 >> op >> amount >> if_s >> r2 >> cmp_str >> val;
		if (CMP_OPS[cmp_str](r2, val)) 
			max_ever = max(max_ever, OPS[op](r1, amount));
	}

	cout << "Max ever: " << max_ever << endl;
	cout << "Final max: " << max_element(reg.begin(), reg.end(),  [](auto&a, auto& b) { return a.second < b.second; })->second << endl;
	return 0;
}
