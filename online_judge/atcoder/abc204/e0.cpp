#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

long long cost(long long c, long long d, long long t, long long a)
{
  if (a < 0) return 1e18;
  return c + (d / (t + a + 1)) + a;
}

long long fn(long long c, long long d, long long t)
{
  int dd = sqrt(d);
  long long ans = cost(c, d, t, 0);
  if (dd < t) return ans;

  for (int i = -5; i < 5; i++) {
    ans = min(ans, cost(c, d, t, dd + i));
  }

  return ans;
}

int main()
{
  int N, M, a, b, c, d;
  cin >> N >> M;
  map<int, vector<pair<int, pair<int, int>>>> MM;

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c >> d;
    a--;b--;
    MM[a].push_back({ b, { c, d }});
    MM[b].push_back({ a, { c, d }});
  }

  vector<long long> D(N + 1, 1e18);
  vector<bool> visited(N + 1, false);
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long >>> que;

  que.push({ 0, 0 });
  D[0] = 0;
  while (que.size()) {
    long long t = que.top().first;
    int node = que.top().second;
    que.pop();
    if (D[node] != t) continue; // ??????

    for (auto& vi: MM[node]) {
      int nn = vi.first;
      long long c = vi.second.first, d = vi.second.second;
      long long vv = fn(c, d, t);
      if (D[nn] > vv + t) {
        D[nn] = vv + t;
        que.push({ D[nn], nn });
      }
    }
  }

  if (D[N-1] == 1e18) {
    cout << -1 << endl;
  } else {
    cout << D[N-1] << endl;
  }

  return 0;
}
