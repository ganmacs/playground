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

int main()
{
  int H, W;
  cin >> H >> W;
  vector<string> M(H);
  for (auto& vi: M) cin >> vi;

  vector<vector<int>> V1(H + 1, vector(W + 1, 0));
  vector<vector<int>> V2(H + 1, vector(W + 1, 0));
  vector<vector<int>> V3(H + 2, vector(W + 2, 0));
  vector<vector<int>> V4(H + 2, vector(W + 2, 0));

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (M[i][j] == '.') {
        V1[i + 1][j + 1] = V1[i + 1][j] + 1;
        V2[i + 1][j + 1] = V2[i][j + 1] + 1;
      } else {
        V1[i + 1][j + 1] = 0;
        V2[i + 1][j + 1] = 0;
      }
    }
  }

  for (int i = H; i > 0; i--) {
    for (int j = W; j > 0; j--) {
      if (M[i-1][j-1] == '.') {
        V3[i][j] = V3[i + 1][j] + 1;
        V4[i][j] = V4[i][j + 1] + 1;
      } else {
        V3[i][j] = 0;
        V4[i][j] = 0;
      }
    }
  }

  long long ans = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (M[i][j] == '#') continue;
      long long a = -4 + 1;
      ans = max(ans, a + V1[i + 1][j + 1] + V2[i + 1][j + 1] + V3[i + 1][j + 1] + V4[i + 1][j + 1]);
    }
  }

  cout << ans << endl;
  return 0;
}
