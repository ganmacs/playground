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

int main()
{
  long long N, A, B, ans = 0;
  cin >> N >> A >> B;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;

  for (int i = 1; i < N; i++) {
    ans += min(A*(V[i]-V[i-1]), B);
  }

  printf("%lld\n", ans);
  return 0;
}
