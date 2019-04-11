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
int A[100][100];

int main(int argc, char *argv[])
{
  int H, W;
  string S[2000];
  queue<pair<int, int> > que;
  cin >> H >> W;
  int b = 0;

  for (int i = 0; i < H; i++) {
    cin >> S[i];

    for (int j = 0; j < W; j++) {
      if (S[i][j] == '#') b++;
      A[i][j] = -1;
    }
  }

  que.push(make_pair(0, 0));
  A[0][0] = 1;

  while (!que.empty()) {
    auto p = que.front();
    que.pop();

    for (int i = 0; i < 4; i++) {
      int dy = p.first + d[i][0];
      int dx = p.second + d[i][1];
      if (0 <= dx && 0 <= dy && dx < W && dy < H && -1 == A[dy][dx] && S[dy][dx] != '#') {
        A[dy][dx] = A[p.first][p.second] + 1;
        que.push(make_pair(dy, dx));
      }
    }
  }

  if (A[H-1][W-1] == -1) {
    cout << -1 << endl;
  } else {
    cout << (H*W) - b - A[H-1][W-1] << endl;
  }

  return 0;
}
