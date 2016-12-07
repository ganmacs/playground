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
static const long long MAX = 100000;
long n, x[MAX + 10], ans[MAX + 10];

long long solve()
{
  fill_n(ans, n + 1, 0);
  long long maxv = 0;

  for (int i = 0; i < n; i++) {
    long long v = ans[x[i]]+ x[i] + 1;
    maxv = max(maxv, v);
    int idx = lower_bound(ans + x[i], ans + n, v) - ans;
    fill(ans + x[i], ans + idx, v);
  }

  return (n * (n + 1) / 2) - maxv;
}

int main(){
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i];
    x[i]--;
  }
  cout << solve() << endl;
}
