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

string S[11];
int vvv = 0;
bool  M[10][10];
int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int dfs(int y, int x, bool v[10][10]) {
  int cnt = 0;
  for (int i = 0; i < 4; i++) {
    int ddy = d[i][1] + y;
    int ddx = d[i][0] + x;
    if ((ddx >= 0) && (ddx < 10) && (ddy >= 0) && (ddy < 10) && v[ddy][ddx]) {
      v[ddy][ddx] = false;
      cnt += 1 + dfs(ddy, ddx, v);
    }
  }
  return cnt;
}

bool t(int y, int x) {
  bool m[10][10];
  for (int i = 0; i < 10; i++) {
    copy(begin(M[i]), end(M[i]), begin(m[i]));
  }

  m[y][x] = true;
  return (dfs(y, x, m) == vvv);
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < 10; i++) {
    cin >> S[i];

    for (int j = 0; j < 10; j++) {
      if (S[i][j] == 'x') {
        M[i][j] = false;
      } else {
        vvv++;
        M[i][j] = true;
      }
    }
  }

  vvv++;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (S[i][j] == 'x' && t(i, j)){
        cout << "YES" << endl;
        return 0;
      }
    }
  }

  cout << "NO" << endl;
  return 0;
}
