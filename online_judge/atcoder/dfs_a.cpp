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

string M[512];
bool A[512][512];
int n, m, sx, sy, gx, gy;

int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

bool dfs(int py, int px) {
  if (M[py][px] == 'g') return true;

  for (int i = 0; i < 4; i++) {
    int ddy = d[i][1] + py;
    int ddx = d[i][0] + px;
    if ((ddx >= 0) && (ddx < m) && (ddy >= 0) && (ddy < n) && !A[ddy][ddx]) {
      A[ddy][ddx] = true;
      if (dfs(ddy, ddx)) {
        return true;
      };
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> M[i];

    for (int j = 0; j < m; j++) {
      if (M[i][j] == 's') {
        sy = i;
        sx = j;
        A[i][j] = true;
      } else if (M[i][j] == 'g') {
        gy = i;
        gx = j;
        A[i][j] = false;
      } else if (M[i][j] == '#') {
        A[i][j] = true;
      } else {
        A[i][j] = false;
      }
    }
  }

  cout << (dfs(sy, sx) ? "Yes" : "No") << endl;
}
