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
  int N, t[123456], x[123456], y[123456];
  cin >> N;
  for (int i = 0; i < N; i++) cin >> t[i] >> x[i] >> y[i];

  int j = 0, nx = 0, ny = 0;
  for (int i = 0; i < N; i++) {
    for (; j < t[i]; j++) {
      if (nx != x[i]) {
        nx += (nx < x[i] ? 1 : -1);
      } else {
        ny += (ny < y[i] ? 1 : -1);
      }
    }

    if (nx != x[i] || ny != y[i]) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
  return 0;
}
