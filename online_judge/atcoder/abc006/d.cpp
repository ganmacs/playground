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

int main(int argc, char *argv[])
{
  int N, c[32322], maxv = 0, dp[32232];
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> c[i];
  }

  for (int i = 0; i < N; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (c[i] > c[j]) {
        dp[i] = max(dp[j] + 1, dp[i]);
      }
    }

    maxv = max(maxv, dp[i]);
  }

  printf("%d\n", N-maxv);
  return 0;
}
