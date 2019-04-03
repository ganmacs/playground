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

int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int M[1100][1100],  B[1000][1000] = {0};
string S[1000];
pair<int, int > n[20];

int main(int argc, char *argv[])
{
  int H, W, N, sx, sy, gy, gx;
  cin >> H >> W >> N;

  for (int i = 0; i < H; i++) {
    cin >> S[i];

    for (int j = 0; j < W; j++) {
      if (S[i][j] == 'S') {
        sx = j;
        sy = i;
      } else if (S[i][j] != '.' && S[i][j] != 'X') {
        n[S[i][j] - '0'] = make_pair(i, j);
      }
    }
  }

  int x = sx, y = sy;
  for (int i = 1; i <= N; i++) {
    queue<pair<int, int> > que;
    bool finish = false;
    bool A[1000][1000] = {};

    gy = n[i].first;
    gx = n[i].second;

    que.push(make_pair(y, x));
    A[y][x] = true;

    while (!que.empty()) {
      pair<int, int> p = que.front();
      que.pop();

      for (int j = 0; j < 4; j++) {
        int ddy = d[j][1] + p.first;
        int ddx = d[j][0] + p.second;
        if ((ddx >= 0) && (ddx < W) && (ddy >= 0) && (ddy < H) && !A[ddy][ddx] && S[ddy][ddx] != 'X') {
          B[ddy][ddx] = B[p.first][p.second] + 1;
          A[ddy][ddx] = true;

          if (ddx == gx && ddy == gy) {
            finish = true;
            break;
          }

          que.push(make_pair(ddy, ddx));
        }
      }

      if (finish) {
        x = gx;
        y = gy;
        break;
      }
    }
  }


  cout << B[n[N].first][n[N].second] << endl;
}
