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
  vector<long long> P(A), Q(B), R(C), PQ;
  for (auto& vi: P) cin >> vi;
  for (auto& vi: Q) cin >> vi;
  for (auto& vi: R) cin >> vi;

  sort(P.begin(), P.end(), greater<long long>());
  sort(Q.begin(), Q.end(), greater<long long>());

  for (int i = 0; i < X; i++) PQ.push_back(P[i]);
  for (int i = 0; i < Y; i++) PQ.push_back(Q[i]);
  for (auto& vi: R) PQ.push_back(vi);
  sort(PQ.begin(), PQ.end(), greater<long long>());

  long long ans = 0;
  for (int i = 0; i < X + Y; i++) ans += PQ[i];

  printf("%lld\n", ans);
  return 0;
}
