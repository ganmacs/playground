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

  for (long long n = 1; n <= 3500; n++) {
    for (long long h = 1; h <= 3500; h++) {
      long long t = n*h*N;
      long long t1 = 4*h*n - N*(h + n);

      if (t1 <= 0) continue;
      if (t % t1 == 0) {
        printf("%lld %lld %lld\n", h, n, t/t1);
        return 0;
      }
    }
  }

  return 0;
}
