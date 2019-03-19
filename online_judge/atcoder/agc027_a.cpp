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
  int N, x, ans = 0, a[1000];
  cin >> N >> x;

  for (int i = 0; i < N; i++) cin >> a[i];
  sort(a, a + N);

  for (int i = 0; i < N; i++) {
    if (x >= a[i]) {
      x -= a[i];
      ans++;
    }
  }
  if (x > 0 && ans == N) ans--;

  printf("%d\n", ans);
}
