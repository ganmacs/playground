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

int N, a, b, dp[514321], bb[514321];
pair<int, int> p[514321];
const int INF = 1<<29;

int main(int argc, char *argv[])
{
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    scanf("%d %d", &a, &b);
    p[i] = make_pair(a, -b);
    dp[i] = INF;
  }
  sort(p, p + N);

  for (int i = 0; i < N; i++) {
    p[i].second = -p[i].second;
  }

  for (int i = 0; i < N; i++) {
    *lower_bound(dp, dp + N, p[i].second) = p[i].second;
  }

  printf("%ld\n", lower_bound(dp, dp + N, INF) - dp);
  return 0;
}
