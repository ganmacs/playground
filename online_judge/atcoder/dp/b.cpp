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

int h[112345];
int dp[112345];

int main(int argc, char *argv[])
{
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  dp[0] = 0;
  for (int i = 1; i < N; i++) {
    int minv = 1e9;
    for (int j = 1; j <= K; j++) {
      if (i-j >= 0) {
        minv = min(minv, dp[i-j] + abs(h[i-j] - h[i]));
      }
    }

    dp[i] = minv;
  }

  cout << dp[N-1] << endl;
  return 0;
}
