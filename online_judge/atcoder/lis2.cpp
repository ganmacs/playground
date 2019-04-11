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

int N, a, b, dp[514321];
pair<int, int> p[514321];
int an = 0;

const int INF = 100000;

int main(int argc, char *argv[])
{
  int N, a[100], dp[100];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    dp[i] = INF;
  }

  for (int i = 0; i < N; i++) {
    *lower_bound(dp, dp + N, a[i]) = a[i];
  }

  printf("%d\n", lower_bound(dp, dp + N, INF)-dp);
  return 0;
}
