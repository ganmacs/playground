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
  long long N, a, b;
  cin >> N;
  vector<pair<long long, long long>> V(N);
  for (auto& vi: V) {
    cin >> a >> b;
    vi = { a+b, a-b };
  }
  sort(V.begin(), V.end());

  long long ans = N, p = -1e18;
  for (auto& vi: V) {
    if (p <= vi.second) {
      p = vi.first;
    } else {
      ans--;
    }
  }

  cout << ans << endl;
  return 0;
}
