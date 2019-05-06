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

int main(int argc, char *argv[])
{
  int N, T, t[200010], dt[200010];
  cin >> N >> T;
  for (int i = 0; i < N; i++) cin >> t[i];
  dt[0] = 0;
  for (int i = 1; i < N; i++) {
    dt[i] = t[i] - t[i-1];
  }

  long long ans = 0;
  for (int i = 1; i < N; i++) {
    ans += min(dt[i], T);
  }
  ans += T;

  cout << ans << endl;
  return 0;
}
