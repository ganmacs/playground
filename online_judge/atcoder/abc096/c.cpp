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

int mm[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int main(int argc, char *argv[])
{
  int H, W;
  string ss[54];
  cin >> H >> W;
  for (int i = 0; i < H; i++) cin >> ss[i];

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (ss[i][j] == '.') continue;

      for (int k = 0; k < 4; k++) {
        int yy = i + mm[k][0];
        int xx = j + mm[k][1];
        if ((yy >= 0) && (yy < H) && (xx >= 0) && (xx < W)) {
          if (ss[yy][xx] == '#' || ss[yy][xx] == 'x') {
            ss[yy][xx] = 'x';
            ss[i][j] = 'x';
          }
        }
      }
    }
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (ss[i][j] == '#') {
        cout << "No" << endl;
        return 0;
      }
    }
  }

  cout << "Yes" << endl;
  return 0;
}
