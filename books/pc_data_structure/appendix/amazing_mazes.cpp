#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <cmath>
#include <queue>

using namespace std;

static const int dx[] = { -1, 0, 0, 1 };
static const int dy[] = { 0, 1, -1, 0 };
static const int MAX = 30 * 30 * 2;
static const int M = 30;

typedef pair<int, int> P;

int maze[MAX + 2][MAX + 2];
int dist[M][M];
int w, h;

int bfs(int y, int x)
{
  queue<P> q;
  q.push(P(y, x));
  dist[y][x] = 1;

  while (!q.empty()) {
    P p = q.front(); q.pop();

    for (int i = 0; i < 4; i++) {
      int yy = p.first + dy[i];
      int xx = p.second + dx[i];

      if (!(xx >= 0 && xx < w && yy >= 0 && yy < h) || dist[yy][xx]) continue;
      if (dx[i] && maze[yy*2][min(xx, p.second)]) continue; // left or right
      if (dy[i] && maze[max(yy, p.first)*2-1][xx]) continue;

      dist[yy][xx] = dist[p.first][p.second] + 1;
      if (yy == h-1 && xx == w-1) return dist[yy][xx];

      q.push(P(yy, xx));
    }
  }
  return 0;
}

int main(){
  while (cin >> w >> h, w || h) {
    for (int i = 0; i < M; i++) fill_n(dist[i], w, 0);
    for (int i = 0; i < (2 * h) - 1; i++) {
      fill_n(maze[i], w, 0);
      int v = (i % 2 == 0) ? (w - 1) : w;
      for (int j = 0; j < v; j++) cin >> maze[i][j];
    }
    cout << bfs(0, 0) << endl;
  }
}
