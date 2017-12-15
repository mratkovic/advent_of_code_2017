#include <bits/stdc++.h>

using namespace std;
const int F[] = {16807, 48271};
const int MODS[] = {4, 8};
const int DIV = 2147483647;
const int LIMIT = 5e6;

int main(int argc, char* argv[]) {
    fstream fs("./input", fstream::in);
    string s;
    int gen[2];
    fs >> s >> s >> s >> s >> gen[0]; // "Generator A starts with 883"
    fs >> s >> s >> s >> s >> gen[1];
    
    auto update_single_step = [&gen](int i) {
        gen[i] = 1L * gen[i] * F[i] % DIV;
        return gen[i];
    };
    auto update_gen = [&update_single_step](int i) {
        while (update_single_step(i) % MODS[i] != 0){}
    };

    auto update = [&update_gen]() {
        update_gen(0);
        update_gen(1);
    };

    update();
    int ans = 0;
    for (int i = 0; i < LIMIT; ++i) {
        update();
        ans += (gen[0] & 0xFFFF) == (gen[1] & 0xFFFF);
    }
    cout << ans << endl;
    return 0;
}
