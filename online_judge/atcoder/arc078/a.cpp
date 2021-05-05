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
  long long s = 0;
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    s += vi;
  };

  long long x = V[0];
  long long y = s-V[0];
  long long ans = abs(x - y);

  for (int i = 1; i < (N-1); i++) {
    x += V[i];
    y -= V[i];
    ans = min(ans, abs(x - y));
  }

  cout << ans << endl;
  return 0;
}
