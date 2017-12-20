#include <iostream>
#include <algorithm>
#include <string>
#include <regex>
#include <functional>
#include <istream>
#include <sstream>
#include <fstream>
#include <set>
#include <list>

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
    bool operator <(const Point3& b) const {
        for (int i = 0; i < LEN; ++i)
            if (data[i] != b.data[i])
                return data[i] < b.data[i];
        return false;
    }
    Point3 operator +(Point3& p) { return op(p, [](int a, int b) {return a + b; }); }
    Point3 operator *(int t) { return op([&t](int a) { return a * t; }); }
};

istream& operator >>(istream& is, Point3& p) {
    is >> p.data[0] >> p.data[1] >> p.data[2];
    return is;
}

struct Particle {
    Point3 p, v, a;

    bool operator <(const Particle& b) const {
        return p < b.p;
    }
    void tick() {
        v = v + a;
        p = p + v;
    }
};

istream& operator >>(istream& is, Particle& p) {
    is >> p.p >> p.v >> p.a;
    return is;
}

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);

    list<Particle> population;
    for (string s; getline(fs, s);) {
        s = regex_replace(s, regex("<|>|,|=|a|p|v"), " ");
        Particle p; istringstream(s) >> p;
        population.emplace_back(p);
    }

    int cnt = 0;
    const int STAGNATION_CNT = 1000;
    for (int it = 0; true; ++it) {
        if (it % STAGNATION_CNT == 0) {
            if (population.size() == cnt) break;
            cnt = population.size();
        }
        multiset<Point3> positions;
        for (auto& p : population) {
            p.tick(); positions.emplace(p.p);
        }
        population.remove_if([&positions](auto& p){ return positions.count(p.p) != 1; });
    }
    cout << population.size() <<  endl;
}
