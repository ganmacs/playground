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
map<long long, long long> V;

void dfs(long long v) {
  if (v>3234566667) return;
  V[v]++;

  int t = v%10;
  for (int i = -1; i <= 1; i++) {
    long long tt = t + i;
    if (tt <= 9 && tt >= 0) {
      dfs(v*10 + tt);
    }
  }
}

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i < 10; i++) dfs(i);
  for (auto& vi: V) {
    N--;
    if (N == 0) {
      printf("%lld\n", vi.first);
      return 0;
    }
  }

  return 0;
}
