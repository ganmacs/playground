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
  unsigned long long L, R, ans = 1e19;
  cin >> L >> R;


  for (unsigned long long int i = L; i < R; i++) {
    if (i % 2019 == 0) {
      cout << 0 << endl;
      return 0;
    }

    for (unsigned long long int j = 1; i + j <= R; j++) {
      if ((i + j) % 2019 == 0) {
        cout << 0 << endl;
        return 0;
      }
      ans = min(ans, (i * (i+j)) % 2019);
    }
  }

  cout << ans << endl;
  return 0;
}
