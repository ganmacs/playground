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

map<int, int> V;

void f(int n) {
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      V[i]++;
      V[n/i]++;
    }
  }
}

int main()
{
  int N, M, ans = 0;
  cin >> N >> M;

  f(M);
  for (auto& vi: V) {
    if (M/vi.first >= N) {
      ans = max(ans, vi.first);
    }
  }

  printf("%d\n", ans);
  return 0;
}
