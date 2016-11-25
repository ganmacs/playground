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

struct m_t {
  int m[N2][N2];
  int x0, y0;
  int dist;

  bool operator < (const m_t &oth) const {
    for (int i = 0; i < N2; i++) {
      for (int j = 0; j < N2; j++) {
        if (oth.m[i][j] == m[i][j]) continue;
        return m[i][j] > oth.m[i][j];
      }
    }
    return false;
  }
};

map<m_t, bool> M;
queue<m_t> Q;
int n;

const int dy[4] = {-1, 0, 0, 1};
const int dx[4] = {0, -1, 1, 0};
int ans[N2][N2] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

void pp(m_t m)
{
  for (int i = 0; i < N2; i++) {
    for (int j = 0; j < N2; j++) {
      cout << m.m[i][j] << " ";
    }
    cout << endl;
  }
}

bool is_goal(m_t m)
{
  for (int i = 0; i < N2; i++) {
    for (int j = 0; j < N2; j++) {
      if (ans[i][j] != m.m[i][j]) return false;
    }
  }
  return true;
}

int bfs(m_t mm)
{
  m_t m, tmp;
  int xx, yy;
  Q.push(mm);
  M[mm] = true;

  while (!Q.empty()) {
    m = Q.front(); Q.pop();

    if (is_goal(m)) return m.dist;

    for (int i = 0; i < 4; i++) {
      yy = dy[i] + m.y0;
      xx = dx[i] + m.x0;
      if (!(0 <= xx && xx < N2 && 0 <= yy && yy < N2)) continue;
      tmp = m;
      swap(tmp.m[yy][xx], tmp.m[m.y0][m.x0]);
      if(!M[tmp]) {
        tmp.y0 = yy;
        tmp.x0 = xx;
        M[tmp] = true;
        tmp.dist += 1;
        Q.push(tmp);
      }
    }
  }

  return -1;
}

int main(){
  m_t m;
  int v;

  m.dist = 0;
  for (int i = 0; i < N2; i++) {
    for (int j = 0; j < N2; j++) {
      cin >> v;
      if (v == 0) {
        m.y0 = i;
        m.x0 = j;
      }
      m.m[i][j] = v;
    }
  }
  cout << bfs(m) << endl;;
}
