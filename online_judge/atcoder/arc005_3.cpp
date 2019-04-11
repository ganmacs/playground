#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

using namespace std;
int H, W;
string M[510];
int A[510][510];

int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
deque<pair<int, int> > que;

int main(int argc, char *argv[])
{
  pair<int, int> s, g;
  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    cin >> M[i];

    for (int j = 0; j < W; j++) {
      A[i][j] = -1;
      if (M[i][j] == 's') {
        s = make_pair(i, j);
        que.push_back(s);
      } else if (M[i][j] == 'g') {
        g = make_pair(i, j);
      }
    }
  }

  A[s.first][s.second] = 0;
  while (!que.empty()) {
    auto p = que.front();
    que.pop_front();

    for (int i = 0; i < 4; i++) {
      int dy = p.first + d[i][0];
      int dx = p.second + d[i][1];
      if (0 <= dx && 0 <= dy && dx < W && dy < H && -1 == A[dy][dx]) {
        if (M[dy][dx] == '#') {
          A[dy][dx] = 1 + A[p.first][p.second];
          que.push_back(make_pair(dy, dx));
        } else {
          A[dy][dx] = A[p.first][p.second];
          que.push_front(make_pair(dy, dx));
        }
      }
    }
  }

  if (A[g.first][g.second] <= 2) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
