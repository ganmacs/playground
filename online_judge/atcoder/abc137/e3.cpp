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

const long long int INF = 1e18;

long long int d[2500];

int main()
{
  int N, M, P, a, b, c;
  cin >> N >> M >> P;
  vector<pair<int, pair<int, long long int >>> V;

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    a--;
    b--;
    V.push_back(make_pair(a, make_pair(b, -(c-P))));
  }

  fill(d, d + N, INF);
  d[0] = 0;

  for (int i = 0; i < N; i++) {
    for (auto& vi: V) {
      int src = vi.first;
      int dst = vi.second.first;
      long long cost = vi.second.second;
      if (d[src] != INF && d[dst] > d[src] + cost) {
        d[dst] = d[src] + cost;
      }
    };
  }

  for (int i = 0; i < N; i++) {
    for (auto& vi: V) {
      int src = vi.first;
      int dst = vi.second.first;
      long long cost = vi.second.second;
      if (d[src] != INF && d[dst] > d[src] + cost) {
        d[dst] = -INF;
      }
    };
  }

  if (-d[N-1] >= INF) {
    cout << -1 << endl;
  } else {
    cout << max((long long int)0, -d[N-1]) << endl;
  }

  return 0;
}
