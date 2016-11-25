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
static const int N = 9;
static const int N2 = 3;

typedef struct m_t {
  int m[N2][N2];
  int x0, y0;
  int dist;
} m_t;

map<m_t, bool> M;
queue<m_t> Q;
int n;

int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};

void bfs(m_t mm)
{
  m_t m, tmp;
  int xx, yy;
  Q.push(mm);

  while (!Q.empty()) {
    m = Q.front(); Q.pop();

    for (int i = 0; i < 4; i++) {
      yy = dy[i] + mm.y0;
      xx = dx[i] + mm.x0;
      if (!(0 <= xx && xx < N2 && yy <= 0 && yy < N2)) continue;
      tmp = m;
      swap(tmp.m[yy][xx], tmp.m[mm.y0][mm.x0]);
      if(!M.at(tmp)) {
        tmp.x0 = xx;
        tmp.y0 = yy;
        M[tmp] = true;
        tmp.dist += 1;
        Q.push(tmp);
      }
    }
  }
}

int main(){
  m_t m;
  int v;

  for (int i = 0; i < N2; i++) {
    for (int j = 0; j < N2; j++) {
      cin >> v;
      if (v == 0) {
        m.x0 = j; m.y0 = i;
      }
      m.m[i][j] = v;
    }
  }
  m.dist = 0;
  bfs(m);
}
