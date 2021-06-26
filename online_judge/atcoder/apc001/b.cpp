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
  int N;
  cin >> N;

  vector<int> a(N), b(N);
  for (auto& vi: a) cin >> vi;
  for (auto& vi: b) cin >> vi;

  long long ans = 0;
  for (long long i = 0; i < N; i++) {
    if (a[i] < b[i]) {
      ans += (b[i]-a[i])/2;
    } else {
      ans -= (a[i]-b[i]);
    }
  }

  if (ans < 0) {
    puts("No");
  } else {
    puts("Yes");
  }
  return 0;
}
