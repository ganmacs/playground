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

int d[10][10];
int dd[10][10];

int main()
{
  int H, W;
  int ans = 0, a;
  cin >> H >> W;
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      cin >> d[i][j];
      dd[i][j] = 1e8;
    }
  }

  for (int k = 0; k <= 9; k++) {
    for (int i = 0; i <= 9; i++) {
      for (int j = 0; j <= 9; j++) {
        dd[i][j] = min(dd[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> a;
      if (a == 1 || a == -1) continue;
      ans += dd[a][1];
    }
  }

  cout << ans << endl;
}
