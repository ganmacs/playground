#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main()
{
  int X, Y, A, B, C;
  cin >> X >> Y >> A >> B >> C;
  vector<int> p(A), q(B), r(C);
  vector<long long> pq, spq(X + Y + 1), sr(C + 1);
  for (auto& vi: p) cin >> vi;
  for (auto& vi: q) cin >> vi;
  for (auto& vi: r) cin >> vi;
  sort(p.begin(), p.end(), greater<int>());
  sort(q.begin(), q.end(), greater<int>());
  sort(r.begin(), r.end(), greater<int>());

  for (int i = 0; i < X; i++) pq.push_back(p[i]);
  for (int i = 0; i < Y; i++) pq.push_back(q[i]);
  sort(pq.begin(), pq.end(), greater<int>());

  spq[0] = 0;
  for (int i = 0; i < X + Y; i++) {
    spq[i + 1] = pq[i] + spq[i];
  }

  sr[0] = 0;
  for (int i = 0; i < C; i++) {
    sr[i + 1] = r[i] + sr[i];
  }

  long long ans = 0;
  for (int i = 0; i <= min(C, X + Y); i++) {
    ans = max(ans, sr[i] + spq[X + Y - i]);
  }

  printf("%lld\n", ans);
  return 0;
}
