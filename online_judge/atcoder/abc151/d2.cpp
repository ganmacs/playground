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
  int H, W, ans = 0;
  cin >> H >> W;
  vector<string> M(H);
  for (int i = 0; i < H; i++) cin >> M[i];

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (M[i][j] == '#') continue;
      queue<pair<int, int>> que;
      vector<vector<int>> V(H, vector(W, -1));
      que.push({i, j});
      V[i][j] = 0;

      while (que.size()) {
        int ii = que.front().first, jj = que.front().second; que.pop();

        for (int k = 0; k < 4; k++) {
          int iii = ii + dy[k];
          int jjj = jj + dx[k];

          if (iii >= 0 && iii < H && jjj >= 0 && jjj < W && M[iii][jjj] != '#' && V[iii][jjj] == -1) {
            V[iii][jjj] = V[ii][jj] + 1;
            ans = max(ans, V[iii][jjj]);
            que.push({iii, jjj});
          }
        }
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
