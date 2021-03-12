#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

char m[105][104];

int main(int argc, char *argv[])
{
  int H, W;
  map<int, bool> hh, ww;

  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    bool f = true;
    for (int j = 0; j < W; j++) {
      cin >> m[i][j];
      if (m[i][j] == '#') {
        f = false;
      }
    }
    hh[i] = f;
  }

  for (int i = 0; i < W; i++) {
    bool f = true;
    for (int j = 0; j < H; j++) {
      if (m[j][i] == '#') {
        f = false;
      }
    }
    ww[i] = f;
  }

  for (int i = 0; i < H; i++) {
    if (hh[i]) continue;
    for (int j = 0; j < W; j++) {
      if (ww[j]) continue;
      cout << m[i][j];
    }
    puts("");
  }

  return 0;
}
