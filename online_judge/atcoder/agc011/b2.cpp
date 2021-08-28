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

int main()
{
  int N, ans = 1;
  cin >> N;
  vector<long long> V(N), V2(N);
  for (auto& vi: V) cin >> vi;
  sort(V.begin(), V.end());
  V2[0] = V[0];
  for (int i = 1; i < N; i++) V2[i] = V2[i-1] + V[i];
  for (int i = N-1; i >= 1; i--) {
    if (V[i] <= (V2[i-1]*2)) {
      ans++;
    } else {
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}
