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

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main()
{
  int H, W;
  cin >> H >> W;
  vector<string> S(H);
  for (auto& vi: S) cin >> vi;

  int ans = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (S[i][j] == '#') continue;
      int ta = 0;

      vector<vector<int>> mm(H, vector(W, -1));
      queue<pair<int, int >> Q;
      mm[i][j] = 0;
      Q.push({i, j});
      while (Q.size()) {
        int ii = Q.front().first, jj = Q.front().second;Q.pop();

        for (int k = 0; k < 4; k++) {
          int yy = dy[k] + ii, xx = dx[k] + jj;
          if (yy < 0 || yy >= H || xx < 0 || xx >= W || mm[yy][xx] != -1 || S[yy][xx] == '#') continue;
          mm[yy][xx] = mm[ii][jj] + 1;
          ta = max(ta, mm[yy][xx]);
          Q.push({ yy, xx });
        }
      }

      ans = max(ans, ta);
    }
  }

  cout << ans << endl;
  return 0;
}
