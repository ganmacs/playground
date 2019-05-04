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
  int N, x, a[123456], b[123456];
  long long ans = 0;
  cin >> N >>  x;

  a[0] = 0;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= N; i++) {
    if(a[i] > (x - a[i-1])) {
      int d = a[i] - (x - a[i-1]);
      ans += d;
      a[i] -= d;
    }
  }

  cout << ans << endl;
  return 0;
}
