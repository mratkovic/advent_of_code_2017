#include <iostream>
#include <algorithm>
#include <string>
#include <regex>
#include <functional>
#include <istream>
#include <sstream>
#include <fstream>

using namespace std;

struct Point3 {
	static const int LEN = 3;
	int data[LEN];

	int operator[](int i) {
		return data[i];
	}

	Point3 op(Point3& p, function<int(int, int)> f) const {
		Point3 rv;
		for (int i = 0; i < LEN; ++i)
			rv.data[i] = f(data[i], p[i]);
		return rv;
	}

	Point3 op(function<int(int)> f) const {
		Point3 rv;
		for (int i = 0; i < LEN; ++i)
			rv.data[i] = f(data[i]);
		return rv;
	}

	int mandist() {
		int ans = 0;
		for (int i = 0; i < LEN; ++i) ans += abs(data[i]);
		return ans;
	}

	bool operator <(Point3& b) { return mandist() < b.mandist(); }
	bool operator !=(Point3& b) { return mandist() != b.mandist(); }
	Point3 operator +(Point3& p) { return op(p, [](int a, int b) {return a + b; }); }
	Point3 operator *(int t) { return op([&t](int a) { return a * t; }); }
};

istream& operator >>(istream& is, Point3& p) {
	is >> p.data[0] >> p.data[1] >> p.data[2];
	return is;
}

struct Particle {
	int id;
	Point3 p, v, a;

	Particle(int id): id(id){}

	bool operator <(Particle& b) {
		if (a != b.a) return a < b.a;
		if (v != b.v) return v < b.v;
		return p < b.p;
	}
};

istream& operator >>(istream& is, Particle& p) {
	is >> p.p >> p.v >> p.a;
	return is;
}

int main(int argc, char* argv[]) {	
	fstream fs("./input", fstream::in);
	vector<Particle> particles;
	int id = 0;

	// p=<2366,784,-597>, v=<-12,-41,50>, a=<-5,1,-2>
	for (string s; getline(fs, s);) {
		s = regex_replace(s, regex("<|>|,|=|a|p|v"), " ");
		Particle p(id++); istringstream(s) >> p;
		particles.emplace_back(p);
	}
	sort(particles.begin(), particles.end());
	cout << particles.front().id << endl;
}
