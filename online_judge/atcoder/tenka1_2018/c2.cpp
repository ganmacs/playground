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
#include <numeric>

using namespace std;

int main()
{

  int N;
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;
  sort(V.begin(), V.end(), greater<long long>());

  long long ans = 0;

  int t = N-2;
  if (N % 2 == 0) {
    for (int i = 0; i < t/2; i++) ans += 2*V[i];
    ans += V[t/2] - V[t/2+1];
    for (int i = t/2+2; i < N; i++) ans -= 2*V[i];
  } else {
    for (int i = 0; i < t/2; i++) ans += 2*V[i];
    ans += V[t/2] + V[t/2+1];
    for (int i = t/2+2; i < N; i++) ans -= 2*V[i];

    long long a2 = 0;
    for (int i = 0; i < (t/2 + 1); i++) a2 += 2*V[i];
    a2 -= (V[t/2 + 1] + V[t/2 + 2]);
    for (int i = t/2+3; i < N; i++) a2 -= 2*V[i];


    ans = max(ans, a2);
  }

  printf("%lld\n", ans);
  return 0;
}
