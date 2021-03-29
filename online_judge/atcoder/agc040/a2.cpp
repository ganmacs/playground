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
#include <numeric>

using namespace std;

int d[512345];

int main()
{
  string s;
  cin >> s;

  int N = s.length();
  fill(d, d + N + 1, 0);
  for (int i = 0; i < N; i++) {
    if (s[i] == '<') {
      d[i + 1] = d[i] + 1;
    }
  }

  for (int i = N-1; i >= 0; i--) {
    if (s[i] == '>') {
      d[i] = max(d[i], d[i + 1] + 1);
    }
  }

  long long ans = 0;
  for (int i = 0; i <= N; i++) {
    ans += d[i];
  };

  cout << ans << endl;

  return 0;
}
