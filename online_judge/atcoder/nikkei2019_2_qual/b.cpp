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

const long long C = 998244353;

long long d[112345];

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);

  int m = 0;

  for (auto& vi: V) {
    cin >> vi;
    d[vi]++;
    m = max(m, vi);
  };

  if (V[0] != 0 || d[0] != 1) {
    cout << 0 << endl;
    return 0;
  }

  long long ans = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < d[i]; j++) {
      ans = (ans * d[i-1]) % C;
    }
  }
  cout << ans << endl;
  return 0;
}
