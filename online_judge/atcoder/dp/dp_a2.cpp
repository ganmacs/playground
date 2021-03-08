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

int N, h[100000], dp[100000];
int main(int argc, char *argv[])
{

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  dp[0] = 0;
  dp[1] = abs(h[1] - h[0]);

  for (int i = 2; i < N; i++) {
    dp[i] = min(abs(h[i-1]-h[i]) + dp[i-1], abs(h[i-2]-h[i]) + dp[i-2]);
  }

  cout << dp[N-1] << endl;
}
