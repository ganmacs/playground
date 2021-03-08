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

int dp[212345][212345];

int
main()
{
  int ans = 1;
  string a = "";
  string S, s1;
  cin >> S;

  // s1 = S[0];
  // dp[0] = 1;
  // for (int i = 0; i < S.length(); i++) {
  //   a = S[i];
  //   if (s1 == a) {
  //     dp[i] = dp[i-1] + 1;
  //   } else {
  //     dp[i] = dp[i-1] + 1;
  //   }
  // }


  cout <<  ans << endl;
  return 0;
}
