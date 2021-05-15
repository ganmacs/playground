#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N;
  unsigned long long ans = 0;
  cin >> N;

  map<int, unsigned long long> M;
  vector<long long> V(N);
  for (auto& vi: V) {
    cin >> vi;
    M[vi % 200]++;
  };

  for (auto& mi: M) {
    ans += mi.second * (mi.second-1) / 2;
  };

  cout << ans << endl;
  return 0;
}
