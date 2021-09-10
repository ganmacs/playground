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
long long N, ans = 0;

void dfs(long long s, int f) {
  if (s > N) return;
  if (f == 0b111) ans++;
  dfs(10*s + 7, f | 0b100);
  dfs(10*s + 5, f | 0b010);
  dfs(10*s + 3, f | 0b001);
}

int main()
{
  cin >> N;
  dfs(0, 0);

  printf("%lld\n", ans);
  return 0;
}
