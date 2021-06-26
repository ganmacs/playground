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
  int X, Y, A, B, C, x;
  cin >> X >> Y >> A >> B >> C;
  long long ans = 0;
  vector<long long> p(A), q(B), r(C);
  for (auto& vi: p) cin >> vi;
  for (auto& vi: q) cin >> vi;
  for (auto& vi: r) cin >> vi;
  sort(p.begin(), p.end(), greater<long long>());
  sort(q.begin(), q.end(), greater<long long>());
  sort(r.begin(), r.end(), greater<long long>());

  vector<int> pq;
  for (int i = 0; i < X; i++) pq.push_back(p[i]);
  for (int i = 0; i < Y; i++) pq.push_back(q[i]);
  sort(pq.begin(), pq.end(), greater<int>());

  vector<long long> spq(X + Y + 1);
  spq[0] = 0;
  for (int i = 0; i < (X + Y); i++) {
    spq[i + 1] = spq[i] + pq[i];
  }

  vector<long long> sr(C + 1);
  sr[0] = 0;
  for (int i = 0; i < C; i++) {
    sr[i + 1] = sr[i] + r[i];
  }

  for (int i = 0; i <= min(C, X + Y); i++) {
    ans = max(ans, (long long)spq[X + Y - i] + (long long)sr[i]);
  }

  cout << ans << endl;

  return 0;
}
