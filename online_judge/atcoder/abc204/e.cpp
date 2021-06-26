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

long long fx(long long c, long long d, long long t, long long a) {
	if (a < 0) return 1e18;
	return c + (d / (t + a + 1)) + a;
}

long long mmm(long long c, long long d, long long t) {
  long long ans = min(fx(c, d, t, d-t), fx(c, d, t, 0)); // t <= x <= d or d < t
  long long vt = sqrt(d) - t;
  if (vt <= 0) return ans;

  for (int i = -5; i <= 5; i++) {
    ans = min(ans, fx(c, d, t, vt + i));
  }

  return ans;
}


int main()
{
  map<long long, vector<pair<long long, pair<long long, long long>>>> V;
  int N, M, a, b, c, d;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c >> d;
    a--;b--;
    V[a].push_back({ b, { c, d }});
    V[b].push_back({ a, { c, d }});
  }

  vector<long long> D(N + 1, 1e18);
  vector<bool> visited(N + 1, false);
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long , long long>>> que;

  que.push({ 0, 0 });
  D[0] = 0;
  while (!que.empty()) {
    long long t = que.top().first, node = que.top().second;
    que.pop();
    visited[node] = true;
		if (D[node] != t) continue;

    for (auto& vi: V[node]) {
      long long v = vi.first, c = vi.second.first, d = vi.second.second;
      if (visited[v]) continue;

      long long vv = mmm(c, d, t);
      if (D[v] > vv + t) {
        D[v] = vv + t;
        que.push({ D[v], v });
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
