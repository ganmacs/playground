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
  int N, A, B;
  long long ans = 0;
  cin >> N >> A >> B;
  vector<long long> V(N), V2;
  for (auto& vi: V) cin >> vi;
  for (int i = 0; i + 1 < N; i++) {
    long long t = (V[i + 1] - V[i])*A;
    if (t < B) {
      ans += t;
    } else {
      ans += B;
    }
  }

  printf("%lld\n", ans);
 return 0;
}
