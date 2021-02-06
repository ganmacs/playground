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

int M[60][60];
bool A[60][60] = {};

int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main(int argc, char *argv[])
{
  int R, C, sy, sx, gy, gx;
  string v[100];
  cin >> R >> C;
  cin >> sy >> sx;
  cin >> gy >> gx;

  for (int i = 0; i < R; i++) {
    cin >> v[i];

    for (int j = 0; j < C; j++) {
      if (v[i][j] == '#') {
        M[i + 1][j + 1] = -1;
      } else {
        M[i + 1][j + 1] = 0;
      }
    }
  }
  queue<pair<int, int> > que;
  que.push(make_pair(sy, sx));
  A[sy][sx] = true;

  while (!que.empty()) {
    pair<int, int> p = que.front();
    que.pop();

    for (int i = 0; i < 4; i++) {
      int dy = p.first + d[i][0];
      int dx = p.second + d[i][1];

      if (dy > 0 && dy < R && dx > 0 && dx < C && M[dy][dx] != -1 && !A[dy][dx]) {
        if (M[dy][dx] == 0) {
          M[dy][dx] = M[p.first][p.second] + 1;
        } else {
          M[dy][dx] = min(M[dy][dx], M[p.first][p.second] + 1);
        }

        A[dy][dx] = true;
        que.push(make_pair(dy, dx));
      }
    }
  }

  printf("%d\n", M[gy][gx]);
  return 0;
}
