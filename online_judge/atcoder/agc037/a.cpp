#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }

int main() {
  string S;
  cin >> S;
  int N = S.size();
  int dp[N + 1][3];

  for (int i = 0; i < (N + 1); i++) {
    fill(dp[i], dp[i] + 3, 0);
  }

  dp[0][1] = 1;

  for (int i = 1; i < N; i++) {
    if (S[i] != S[i-1]) { // 1 -> 1
      chmax(dp[i][1], dp[i-1][1] + 1);
    }

    if (i >= 3 && (S[i] != S[i-2] || S[i-1] != S[i-3])) { // 2 -> 2
      chmax(dp[i][2], dp[i-2][2] + 1);
    }

    if (i >= 2) {               // 1 -> 2
      chmax(dp[i][2], dp[i-2][1] + 1);
    }

    // 2 -> 1
    chmax(dp[i][1], dp[i-1][2] + 1);
  }

  cout << max(dp[N-1][1], dp[N-1][2]) << endl;
  return 0;
}
