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
  int n, ans = 1;
  long long a[200000], b[200000];
  cin >> n;

  cin >> a[0];
  for (int i = 1; i < n; i++) {
    cin >> a[i];
    b[i] = a[i] - a[i-1];
  }

  for (int i = 1; i < n; i++) {
    // -1 0 1 !!
    if (b[i-1]*b[i] < 0) {
      ans++;
      i++;
    }
  }

  printf("%d\n", ans);
  return 0;
}
