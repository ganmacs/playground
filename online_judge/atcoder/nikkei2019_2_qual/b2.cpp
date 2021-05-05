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

unsigned long long int M = 998244353;

int
main()
{
  int N, a, ma = 0;
  cin >> N;
  map<int, int> V;
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (i == 0 &&  a != 0) {
      cout << 0 << endl;
      return 0;
    }

    ma = max(ma, a);
    V[a]++;
  }

  if (V[0] != 1) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long int ans = 1;
  for (int i = 1; i <= ma; i++) {
    if (V[i] == 0) {
      cout << 0 << endl;
      return 0;
    }

    for (int j = 0; j < V[i]; j++) {
      ans = (ans * V[i-1]) % M;
    }
  }

  cout << ans << endl;
  return 0;
}
