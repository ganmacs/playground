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
  unsigned long long x;
  cin >> x;

  unsigned long long v = x/11;
  unsigned long long ans = v*2;

  if (x % 11 != 0) {
    if ((x % 11) > 6) {
      ans += 2;
    } else {
      ans += 1;
    }
  }

  cout << ans << endl;
  return 0;
}
