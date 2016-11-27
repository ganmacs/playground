#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int WH = 1000;
static const int INF = 10000000;
static const int dx[] = {-1, 0, 0, 1};
static const int dy[] = {0, -1, 1, 0};
int M[WH][WH]; // '.' is 0, 'S' is -2 and 'X' is -1.

typedef pair<int, int> P;

int main(){
  char c;
  int H, W, N, sx, sy;
  int dist[WH][WH], power = 1;
  queue<P> q;
  cin >> H >> W >> N;

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      dist[i][j] = INF;
      cin >> c;
      if (c == '.') {
        M[i][j] = 0;
      } else if(c == 'S') {
        sy = i;
        sx = j;
        M[i][j] = -1;
      } else if (c == 'X'){
        M[i][j] = -2;
      } else {
        M[i][j] = c - '0';
      }
    }
  }

  q.push(make_pair(sy, sx));
  dist[sy][sx] = 0;
  while (!q.empty()) {
    P p = q.front(); q.pop();
    for (int i = 0; i < 4; i++) {
      int yy = p.first + dy[i];
      int xx = p.second + dx[i];
      if (xx < 0 || xx >= W || yy < 0 || yy >= H || -1 > M[yy][xx]) continue;

      if (dist[yy][xx] == INF) {
        dist[yy][xx] = dist[p.first][p.second] + 1;

        if (M[yy][xx] == power) {
          power++;
          if (power > N) {
            cout << dist[yy][xx] << endl;
            return 0;
          }

          while (!q.empty()) q.pop();
          for (int k = 0; k < H; k++) {
            for (int j = 0; j < W; j++) {
              if (k == yy && j == xx) continue;
              dist[k][j] = INF;
            }
          }
          i = 4;                // to skip the last indext
        }

        q.push(make_pair(yy, xx));
      }
    }
  }
}
