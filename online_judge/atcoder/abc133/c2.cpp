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

  unsigned long long ans = 1e19;
  for (int i = 0; (i + 1) <= min((R-L), (unsigned long long)2020); i++) {
    for (int j = i + 1; j <= min((R-L), (unsigned long long)2020); j++) {
      ans = min(ans, ((L + i) * (L + j)) % 2019);
    }
  }

  cout << ans << endl;
  return 0;
}
