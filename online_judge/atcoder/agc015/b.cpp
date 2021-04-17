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

int main()
{
  string s;
  cin >> s;
  long long ans = 0,  N = s.length();

  for (int i = 0; i < N-1; i++) {
    if (s[i] == 'U') {
      ans += ((N-1)-i);
    } else {
      ans += 2*((N-1)-i);
    }
  }

  for (int i = N-1; i >= 1; i--) {
    if (s[i] == 'D') {
      ans += i;
    } else {
      ans += 2*i;
    }
  }

  cout << ans << endl;
  return 0;
}
