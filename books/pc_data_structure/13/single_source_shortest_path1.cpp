#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = (1 << 21);
int n;
int M[MAX][MAX], cost[MAX];
bool vist[MAX];

void dijkstra()
{
  cost[0] = 0;

  while (1) {
    int v = -1;
    for (int i = 0; i < n; i++) {
      if (!vist[i] && (v == -1 || cost[i] < cost[v])) v = i;
    }

    if (v == -1) break;
    vist[v] = true;

    for (int i = 0; i < n; i++) {
      cost[i] = min(cost[i], cost[v] + M[v][i]);
    }
  }
}

int main()
{
  int u, k, v, c;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cost[i] = INF;
    vist[i] = false;
    for (int j = 0; j < n; j++)
      M[i][j] = INF;
  }

  for (int i = 0; i < n; i++) {
    cin >> u >> k;
    for (int j = 0; j < k; j++) {
      cin >> v >> c;
      M[u][v] = c;
    }
  }

  dijkstra();

  for (int i = 0; i < n; i++) {
    cout << i << " " << cost[i] << endl;
  }
  return 0;
}
