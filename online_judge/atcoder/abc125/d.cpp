#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main()
{
  int N, nn = 0;
  unsigned long long int ans = 0;
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) {
    cin >> vi;

    if (vi < 0) {
      nn++;
      vi = -vi;
    }

    ans += (unsigned long long)vi;
  };

  if (nn % 2 == 0) {
    cout << ans << endl;
  } else {
    sort(V.begin(), V.end());
    cout << (ans-(2*V[0])) << endl;
  }

  return 0;
}
