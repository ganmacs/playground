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

char S[102][102];
int ans[102][102];

int main()
{
  int H, W;
  cin >> H >> W;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      ans[i][j] = 1e9;
      cin >> S[i][j];
    }
  }

  ans[0][0] = S[0][0] == '#';

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (i == 0 && j == 0) continue;

      if (S[i][j] == '#') {
        if (j != 0) {
          ans[i][j] = ans[i][j-1] + (S[i][j-1] == '.');
        }

        if (i != 0) {
          ans[i][j] = min(ans[i][j], ans[i-1][j] + (S[i-1][j] == '.'));
        }
      } else {
        if (j != 0) {
          ans[i][j] = ans[i][j-1];
        }

        if (i != 0) {
          ans[i][j] = min(ans[i][j], ans[i-1][j]);
        }
      }
    }
  }

  cout << ans[H-1][W-1] << endl;
  return 0;
}
