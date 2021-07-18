#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main()
{
  int H, W, A, B;
  cin >> H >> W >> A>>B;

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (A > j && B > i) {
        cout << 0;
      } else if (A <= j && B <= i) {
        cout << 0;
      } else {
        cout << 1;
      }
    }
    puts("");
  }

  return 0;
}
