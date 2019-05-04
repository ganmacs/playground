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

const int INF = 1e9;

const int diff[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int main(int argc, char *argv[])
{
  int H, W, ans[1020][1020], aaa = 0;
  string A[1020];
  queue<pair<int, int> > que, que2;
  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    cin >> A[i];

    for (int j = 0; j < W; j++) {
      if (A[i][j] == '#') {
        que.push(make_pair(i, j));
      }
      ans[i][j] = 0;
    }
  }

  while (!que.empty()) {
    while (!que.empty()) {
      auto p = que.front();
      que.pop();

      int i = p.first;
      int j = p.second;
      for (int k = 0; k < 4; k++) {
        int ii = i + diff[k][0];
        int jj = j + diff[k][1];
        if (ii >= 0 && jj >= 0 && ii < H && jj < W && A[ii][jj] == '.') {
          que2.push(make_pair(ii, jj));
          ans[ii][jj] = ans[i][j] + 1;
          aaa = max(ans[ii][jj], aaa);
        }
      }
    }

    while (!que2.empty()) {
      auto p = que2.front();
      que2.pop();
      A[p.first][p.second] = '#';
      que.push(p);
    }
  }

  cout << aaa << endl;
  return 0;
}
