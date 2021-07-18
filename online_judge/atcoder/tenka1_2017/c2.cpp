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
  long long N;
  cin >> N;

  for (long long i = 1; i <= 3500; i++) {
    for (long long j = 1; j <= 3500; j++) {
      auto v1 = i*j;
      auto v2 = i + j;
      auto tt = (4*v1)-(N*v2);
      auto tt2 = N*v1;
      if (tt <= 0) continue;
      if (tt2%tt == 0) {
        printf("%lld %lld %lld\n", i, j, tt2/tt);
        return 0;
      }
    }
  }

  return 0;
}
