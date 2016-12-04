#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;
typedef pair<int, int> P;
typedef pair<int, P> P2;

static const int INF = 1000000;
static const int MAX = 10010;
static const int MAX_c = 22;
static const int MAX_c2 = 50;
vector<P2 > vec[MAX];

int gcout[MAX_c];
int costs[MAX_c2];
int point[MAX_c2];

int main()
{
  int N, M, C, S, G, x, y, d, c;
  while (cin >> N >> M >> C >> S >> G, N||M||C||S||G) {
    for (int i = 0; i < M; i++) {
      S--; G--;
      cin >> x >> y >> d >> c;
      x--; y--;
      vec[x].push_back(P2(d, P(c, y)));
      vec[y].push_back(P2(d, P(c, x)));
    }

    for (int i = 0; i < C; i++) cin >> gcout[i];
    for (int i = 0; i < C; i++) {
      for (int j = 0; j < gcout[i]-1; j++) cin >> point[i];
      for (int j = 0; j < gcout[i]; j++) cin >> costs[j];
    }

    int ans[MAX_c2];
    fill_n(ans, MAX_c2, INF);
    priority_queue<P2> que;
    ans[S] = 0;
    que.push(P2(0, P(-1, S)));
    while (!que.empty()) {
      P2 p = que.top(); que.pop();
      int idx = p.second.second;
      if (ans[idx] < p.first) continue;

      for (int i = 0; i < (int)vec[idx].size(); i++) {
        P2 p2 = vec[idx][i];
        int next = p2.second.second;

        int dist = p2.first;
        int ccc = 0;
        if (p2.second.first == p.second.first) { // same train
          dist += p.first;
        } else {
          ccc += p.first;
        }
        for (int j = 0; j < gcout[i] && dist > 0; j++) {
          if (point[i] < dist) {
            ccc += (point[i] * costs[i]);
          } else {
            ccc += (dist * costs[i]);
          }
          dist -= point[i];
        }

        if (ans[next] > p2.first + ans[idx]) {
          ans[next] = p2.first + ans[idx];
          que.push(p2);
        }
      }
    }

    cout << (ans[G] == INF ? -1 : ans[G]) << endl;
  }
}
