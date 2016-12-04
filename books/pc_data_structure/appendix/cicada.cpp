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
typedef pair<int,int> P;
static const double EPS = 1e-8;
static const int MAX = 100000;
static const int dx[] = {1, 0};
static const int dy[] = {0, 1};

int n;

int G[52][52];
int M[52][52];
bool vist[52][52];

int main()
{
  int h, w;
  char c;

  scanf("%d %d", &h, &w);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (scanf("%c", &c), c == '\n') scanf("%c", &c);
      G[i][j] = M[i][j] = c - '0';
      vist[i][j] = false;
    }
  }

  queue<P> q;
  q.push(P(0, 0));

  while (!q.empty()) {
    P p = q.front(); q.pop();
    for (int i = 0; i < 2; i++) {
      int yy = dy[i] + p.first;
      int xx = dx[i] + p.second;

      if (!(xx >= 0 && yy >= 0 && yy < h && xx < w)) continue;
      if (vist[yy][xx]) continue;

      vist[yy][xx] = true;

      if (xx > 0 && yy > 0) {
        M[yy][xx] += min(M[yy-1][xx], M[yy][xx-1]);
      } else if (xx > 0) {
        M[yy][xx] += M[yy][xx-1];
      } else {
        M[yy][xx] += M[yy-1][xx];
      }
      q.push(P(yy, xx));
    }
  }
  cout << M[h-1][w-1] << endl;
}
