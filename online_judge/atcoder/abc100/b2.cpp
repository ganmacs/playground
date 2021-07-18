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
  int D, N;
  cin >> D >> N;

  int kk = pow(100, D);

  int j = 0;
  for (int i = kk; i <= kk*N + kk; i++) {
    if (i % kk == 0) {
      int t = i/kk;
      if (t % 100 != 0) {
        j++;
        if (j == N) {
          printf("%d\n", i);
          return 0;
        }
      }
    }
  }

  return 0;
}
