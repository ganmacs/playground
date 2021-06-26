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

vector<string> V;
int H, W;

const int dx[4] = { 0, 1, -1, 0 };
const int dy[4] = { 1, 0, 0, -1 };

int bfs(int y, int x) {
  queue<pair<int, int>> Q;
  vector<vector<int>> dis(H, vector(W, -1));

  int res = 0;
  Q.push({ y, x });
  dis[y][x] = 0;

  while (!Q.empty()) {
    int y = Q.front().first, x = Q.front().second;
    Q.pop();
    res = max(res, dis[y][x]);

    for (int i = 0; i < 4; i++) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= W || yy < 0 || yy >= H || V[yy][xx] == '#' || dis[yy][xx] != -1) {
        continue;
      }
      dis[yy][xx] = dis[y][x] + 1;
      Q.push({ yy, xx });
    }
  }

  return res;
}

int main()
{
  cin >> H >> W;
  string S;
  for (int i = 0; i < H; i++) {
    cin >> S;
    V.push_back(S);
  }

  int ans = 0;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (V[y][x] == '#') continue;
      ans = max(ans, bfs(y, x));
    }
  }

  cout<< ans << endl;
  return 0;
}
