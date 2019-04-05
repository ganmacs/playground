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
  string s, t;
  cin >> s;
  cin >> t;
  int dp[3003][3003];

  std::fill(dp[0], dp[0] + 3003, 0);
  for (int i = 1; i <= s.size(); i++) {
    std::fill(dp[i], dp[i] + 300, 0);
    for (int j = 1; j <= t.size(); j++) {
      if (s[i-1] == t[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }

  int i = s.size(), j = t.size();
  string ret = "";
  while (i > 0 && j > 0) {
    if (s[i-1] == t[j-1]) {
      ret += s[i-1];
      i--, j--;
    } else if (dp[i][j-1] > dp[i-1][j]) {
      j--;
    } else {
      i--;
    }
  }

  reverse(ret.begin(), ret.end());
  puts(ret.c_str());

  return 0;
}
