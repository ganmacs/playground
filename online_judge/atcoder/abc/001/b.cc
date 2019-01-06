#include <algorithm>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    unsigned int m;
    cin >> m;

    if (m < 100) {
        printf("00\n");
    } else if (m <= 5000) {
        int v = m / 100;
        printf("%02d\n", v);
    } else if (6000 <= m && m <= 30000) {
        int v = m / 1000;
        printf("%02d\n", v + 50);
    } else if (35000 <= m && m <= 70000) {
        int v = m / 1000;
        printf("%02d\n", ((v - 30) / 5) + 80);
    } else if (m > 70000) {
        printf("89\n");
    }

    return 0;
}
