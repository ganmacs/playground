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

  int t = pow(100, D);
  int j = 0;
  for (int i = 1; i < 1000; i++) {
    if (i % 100) {
      j++;

      if (j == N) {
        printf("%d\n", t*i);
      }
    }
  }
  return 0;
}
