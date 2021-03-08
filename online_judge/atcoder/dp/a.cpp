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
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  dp[0] = 0;
  dp[1] = abs(h[0] - h[1]);
  for (int i = 2; i < N; i++) {
    dp[i] = min(dp[i-1] + abs(h[i-1] - h[i]), dp[i-2] + abs(h[i-2] - h[i]));
  }

  cout << dp[N-1] << endl;
  return 0;
}
