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
  int N;
  cin >> N;
  vector<long long> V(N), B(N, 0), ans;
  for (auto& vi: V) cin >> vi;

  for (int i = N-1; i >= 0; i--) {
    int a = 0;
    int j = i;

    while (j <= N-1) {
      a += B[j];
      j += (i + 1);
    }

    if (a % 2 != V[i]) {
      B[i] = 1;
      ans.push_back(i + 1);
    }
  }

  printf("%ld\n", ans.size());
  for (auto& vi: ans) {
    printf("%lld\n", vi);
  }

  return 0;
}
