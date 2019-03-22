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

string s;
const string w[4] = {"dream", "dreamer", "erase", "eraser"};
bool dp[200000];

int main(int argc, char *argv[])
{
  cin >> s;

  for (int i = 0; i < s.size(); i++) dp[i] = false;

  dp[0] = true;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < 4; j++) {
      if (!dp[i]) continue;
      if (s.substr(i, w[j].size()) == w[j]) {
        dp[i + w[j].size()] = true;
      }
    }
  }

  puts(dp[s.size()] ? "YES" : "NO");

  return 0;
}
