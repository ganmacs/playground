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
#include <algorithm>

using namespace std;

int main()
{
  long long N;
  cin >> N;

  for (long long i = 1; i <= 3500; i++) {
    for (long long j = 1; j <= 3500; j++) {
      long long t = i*j;
      long long tt = 4*t - N*(i + j);
      if (tt <= 0) {
        continue;
      }

      if ((N*t)%tt == 0) {
          printf("%lld %lld %lld\n", i, j, (N*t)/tt);
          return 0;
        }
        }
    }

    return 0;
  }
