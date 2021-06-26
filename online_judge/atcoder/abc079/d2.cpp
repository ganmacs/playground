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

int d[20][20], dd[20][20];

int main()
{
  int H, W, a;
  cin >> H >> W;


  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cin >> d[i][j];
    }
  }

  for (int k = 0; k < 10; k++) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  long long ans = 0, aa;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> a;
      if (a == -1 || a == 1) continue;
      ans += d[a][1];
    }
  }

  cout << ans << endl;
  return 0;
}
