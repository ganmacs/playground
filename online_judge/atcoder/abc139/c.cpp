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

long int H[112345];

int main()
{
  int N;
  cin >> N;

  long int prev = -1, cur, ans = 0;
  H[0] = 0;

  for (int i = 0; i < N; i++) {
    cin >> cur;

    if (cur <= prev) {
      H[i] = H[i-1] + 1;
    } else {
      H[i] = 0;
    }

    ans = max(ans, H[i]);

    prev = cur;
  }


  cout << ans << endl;
  return 0;
}
