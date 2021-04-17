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
  unsigned long long L, R;
  cin >> L >> R;

  if (R - L >= 2019) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long int ans = 1e19;
  for (unsigned long long i = L; i <= (R-1); i++) {
    for (unsigned long long j = 1; L + j <= R; j++) {
      ans = min((i * (L + j)) % 2019, ans);
    }
  }

  cout << ans << endl;
  return 0;
}
