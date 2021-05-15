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

int
main()
{
  string S;
  cin >> S;
  int N = S.size();

  unsigned long long ans = 0;

  for (int i = 0; i < pow(2, N); i++) {
    unsigned long long v = 0;

    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        ans += v;
        v = 0;
      } else {
        v *= 10;
        v += (int)(S[j]-'0');
      }
    }

    ans += v;
  }

  cout << ans << endl;

  return 0;
}
