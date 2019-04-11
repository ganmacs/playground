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
  int N, a[100], dp[100];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) {
        dp[i] = max(dp[j] + 1, dp[i]);
      }
    }

    ans = max(ans, dp[i]);
  }

  printf("%d\n", ans);
  return 0;
}
