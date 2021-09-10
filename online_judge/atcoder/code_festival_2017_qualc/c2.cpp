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

int main()
{
  string S;
  cin >> S;
  int N = S.size(), ans = 0;

  int l = 0, r = N-1;
  while (l < r) {
    if (S[l] == S[r]) {
      l++;
      r--;
    } else if (S[l] == 'x') {
      ans++;
      l++;
    } else if (S[r] == 'x') {
      ans++;
      r--;
    } else {
      puts("-1");
      return 0;
    }
  }

  printf("%d\n", ans);
  return 0;
}
