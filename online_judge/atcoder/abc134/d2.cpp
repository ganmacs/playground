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

int d[212345];

int main()
{
  int N;
  cin >> N;
  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];
  fill(d, d + N + 1, 0);

  int ans = 0;

  for (int i = N; i >= 1; i--) {
    int t = 0;
    for (int j = 1; j * i <= N; j++) {
      t += d[j*i];
    }

    if ((t % 2) != A[i]) {
      ans++;
      d[i] = 1;
    }
  }

  printf("%d\n", ans);
  for (int i = 1; i <= N; i++) {
    if (d[i] == 1) {
      printf("%d\n", i);
    }
  }


  return 0;
}
