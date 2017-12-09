#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <tuple>

using namespace std;

enum OP {
    IGNORE = '!',
    END_GARBAGE = '>',
    BEGIN_GARBAGE = '<',
    BEGIN_GROUP = '{',
    END_GROUP = '}',
};

pair<int, int> find_garbage_end_idx(string in, int i) {
    int dels = 0;
    for (; i < in.size(); ++i) {
        switch (in[i]) {
            case END_GARBAGE:
                return {i, dels};
            case IGNORE:
                ++i; break;
            default:
                ++dels;
        }

    }
    assert(false);
    return {i, dels};
}

int main() {
    fstream fs ("./input", fstream::in);
    string in; fs >> in;
    int depth = 0, sum = 0, garbage = 0, dels;
    for (int i = 0; i < in.size(); ++i) {
        switch (in[i]) {
            case BEGIN_GARBAGE:
                tie(i, dels) = find_garbage_end_idx(in, i+1);
                garbage += dels;
                break;
            case BEGIN_GROUP:
                sum += ++depth;
                break;
            case END_GROUP:
                depth--;

        }
    }
    cout << sum << endl;
    cout << garbage << endl;
    return 0;
}
