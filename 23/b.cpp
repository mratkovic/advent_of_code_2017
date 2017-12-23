#include <bits/stdc++.h>

using namespace std;

/*
// direct assembly rewrite in C
// -> h simply tracks number of prim numbers in range [b, c]

int main(int argc, char* argv[]) {
    int h = 0;
    int b = 84 * 100 + 100000;
    int c = b + 17000;
    for (int f = 1, d = 2; c != b; b += 17) {
        for (int d = 2; d != b; ++d) {
            for (int e = 2; e != b; ++e) {
                if (d*e == b)
                    f = 0;
            }
        }
        if (!f)
            h++;
    }
    return 0;
}
*/

int main(int argc, char* argv[]) {
    int h = 0;
    int b = 84 * 100 + 100000;
    int c = b + 17000;

    for (; b <= c; b += 17) {
        for (int d = 2; d*d <= b; ++d) {
            if (b % d == 0) {
                h++;
                break;
            }
        }
    }
    cout << h << endl;
    return 0;
}
