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

typedef pair<int, int> P;
typedef pair<long long, int> PL;

long long f(long long c, long long d, long long t, long long a) {
  if (a < 0) {
    return 1e18;
  }

  return c + a + (d / (t + 1 + a));
}

long long calc(long long c, long long d, long long t) {
  long long ds = sqrt(d);
  long long ans = f(c, d, t, 0);
  if (t > ds) return ans;

  for (int i = -5; i <= 5; i++) {
    ans = min(ans, f(c, d, t, ds + i));
  }

  return ans;
}

int main()
{
  int N, M, a, b, c, d;
  cin >> N >> M;
  map<int, vector<pair<int, P>>> MM;

  for (int i = 0; i < M; i++) {
    cin >> a >> b >> c >> d;
    a--;b--;
    MM[a].push_back({b, { c, d}});
    MM[b].push_back({a, { c, d}});
  }

  vector<long long> D(N + 1, 1e18);
  priority_queue<PL, vector<PL>, greater<PL>> que;
  que.push({ 0, 0});
  D[0] = 0;
  while (que.size()) {
    long long t = que.top().first;
    int node = que.top().second;
    que.pop();
    if (D[node] < t) continue;

    for (auto& vi: MM[node]) {
      int nn = vi.first;
      long long c = vi.second.first, d = vi.second.second;
      long long vv = calc(c, d, t);
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
