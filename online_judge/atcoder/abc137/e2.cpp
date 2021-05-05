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

int main()
{
  int N, M, P, a, b, c ;
  cin >> N >> M >> P;
  vector<pair<int, pair<int, long long int> > > E(M);

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c;
    E.push_back(make_pair(a-1, make_pair(b-1, -(c-P))));
  }

  vector<long long int> vv(N);
  fill(vv.begin(), vv.end(), INF);

  vv[0] = 0;
  for (int k = 0; k < N; k++) {
    for (auto& vi: E) {
      auto prev = vi.first;
      auto next = vi.second.first;
      auto cost = vi.second.second;
      if (vv[prev] != INF && vv[next] > cost + vv[prev]) {
        vv[next] = cost + vv[prev];
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (auto& vi: E) {
      auto prev = vi.first;
      auto next = vi.second.first;
      auto cost = vi.second.second;
      if (vv[prev] != INF && vv[next] > cost + vv[prev]) {
        vv[next] = -INF;
      }
    }
  }

  if (-vv[N-1] >= INF) {
    cout << -1 << endl;
  } else {
    cout << max((long long int)0, -vv[N-1]) << endl;
  }

  return 0;
}
