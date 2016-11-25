#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

static const int N = 4;
static const int N2 = 16;
static const int dy[] = {-1, 0, 0, 1};
static const int dx[] = {0, -1, 1, 0};

#define Y(v) (v / N)
#define X(v) (v % N)
#define P(y, x) ((y * N) + x)

struct m_t {
  int m[N2], s, md, cost;

  bool operator < (const m_t &oth) const {
    for (int i = 0; i < N2; i++) {
      if (oth.m[i] == m[i]) continue;
      return m[i] < oth.m[i];
    }
    return false;
  }
};

struct state {
  m_t mt;
  int ev;

  bool operator < (const state &oth) const { return ev > oth.ev; }
};

int MD[N2][N2];

int amd(m_t m)
{
  int ans = 0;
  for (int i = 0; i < N2; i++) {
    if (m.m[i] == N2) continue;
    ans += MD[m.m[i]-1][i];
  }
  return ans;
}

int vvv = 0;

int bfs(m_t mm)
{
  priority_queue<state> Q;
  map<m_t, bool> M;
  m_t m, tmp;
  state init;

  mm.cost = 0;
  mm.md = amd(mm);

  init.mt = mm;
  init.ev = mm.md;
  Q.push(init);

  while (!Q.empty()) {
    state s = Q.top(); Q.pop();
    m = s.mt;
    if (m.md == 0) return m.cost;
    M[m] = true;

    for (int i = 0; i < 4; i++) {
      int yy = dy[i] + Y(m.s);
      int xx = dx[i] + X(m.s);
      if (!(0 <= xx && xx < N && 0 <= yy && yy < N)) continue;
      tmp = m;

      tmp.md -= MD[tmp.m[P(yy, xx)]-1][P(yy, xx)];
      tmp.md += MD[tmp.m[P(yy, xx)]-1][m.s];

      swap(tmp.m[P(yy, xx)], tmp.m[m.s]);
      tmp.s = P(yy, xx);

      if (!M[tmp]) {
        vvv++;
        tmp.cost++;
        state news;

        news.mt = tmp;
        news.ev = tmp.cost + tmp.md;
        Q.push(news);
      }
    }
  }
  return -1;
}

int main(){
  m_t m;
  int v;

  for (int i = 0; i < N2; i++) {
    for (int j = 0; j < N2; j++) {
      MD[i][j] = abs(Y(i) - Y(j)) + abs(X(i) - X(j));
    }
  }

  for (int i = 0; i < N2; i++) {
    cin >> v;
    m.m[i] = v;
    if (v == 0) {
      m.m[i] = N2;
      m.s = i;
    }
  }

  cout << bfs(m) << endl;;
}
