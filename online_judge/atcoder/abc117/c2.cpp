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
  int N, M;
  cin >> N >> M;
  vector<int> V(M), T;
  for (auto& vi: V) cin >> vi;
  sort(V.begin(), V.end());
  for (int i = 1; i < M; i++) T.push_back(V[i]-V[i-1]);
  sort(T.begin(), T.end(), greater<int>());

  long long ans = 0;
  for (auto& vi: T) {
    if (N != 1) {
      N--;
      continue;
    }

    ans += vi;
  }

  printf("%lld\n", ans);
  return 0;
}
