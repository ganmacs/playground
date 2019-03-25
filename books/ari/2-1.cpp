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

int a[20];
int N, k;

bool dfs(int p, long long sum) {
  if (p == N) return sum == k;
  return dfs(p + 1, a[p] + sum) && dfs(p + 1, sum);
}

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
  cin >> k;
  printf("%s\n", dfs(0, 0) ? "Yes" : "No");
  return 0;
}
