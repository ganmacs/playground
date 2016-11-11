#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> P;

const int MAX = 10000;
const int INF = (1 << 21);
int n;
// to, cost
vector<P> M[MAX];
int cost[MAX];

void dijkstra(int s)
{
  priority_queue<P, vector<P>, greater<P> > Q;
  for (int i = 0; i < n; i++) cost[i] = INF;
  cost[0] = 0;
  // elm, cost
  Q.push(make_pair(s, 0));

  while (!Q.empty()) {
    pair<int, int> p = Q.top(); Q.pop();
    int v = p.first;
    if (cost[v] < p.second) continue;

    for (int i = 0; i < (int)M[v].size(); i++) {
      pair<int,int> vv = M[v][i];
      if (cost[v] + vv.second < cost[vv.first]) {
        cost[vv.first] = cost[v] + vv.second;
        Q.push(vv);
      }
    }
  }
}

int main()
{
  int u, k, v, c;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> u >> k;
    for (int j = 0; j < k; j++) {
      cin >> v >> c;
      M[u].push_back(P(v, c));
    }
  }

  dijkstra(0);

  for (int i = 0; i < n; i++) {
    cout << i << " " << cost[i] << endl;
  }
  return 0;
}
