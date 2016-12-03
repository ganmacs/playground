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
typedef pair<int, int> P;
static const int MAX = 110;
static const int INF = 1000010;
int n;

int main() {
  int n, m, a, b, c, d;

  while (cin >> n >> m, n || m) {

    vector<P> ils[MAX];
    int dist[MAX];
    for (int i = 0; i < m; i++) {
      cin >> a;

      if (a == 0) {
        cin >> b >> c;
        b--; c--;

        // dijkstra
        bool vist[MAX];
        fill_n(dist, n, INF);
        fill_n(vist, n, false);
        dist[b] = 0;
        priority_queue<P> que;
        que.push(P(0, b));

        while (!que.empty()) {
          P p = que.top(); que.pop();
          int v = p.second;
          if (dist[v] < p.first) continue;

          for (int i = 0; i < (int)ils[v].size(); i++) {
            P vv = ils[v][i];
            if (dist[v] + vv.first < dist[vv.second]) {
              dist[vv.second] = dist[p.second] + vv.first;
              que.push(vv);
            }
          }
        }

        cout << (dist[c] == INF ? -1 : dist[c]) << endl;
      } else {
        cin >> b >> c >> d;
        b--;c--;

        ils[b].push_back(P(d, c));
        ils[c].push_back(P(d, b));
      }
    }
  }


}
