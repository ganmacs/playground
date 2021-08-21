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
      long long t = N*h*n;
      long long t2 = 4*h*n - N*(h + n);

      if (t2 <= 0) continue;

      if (t % t2 == 0) {
        printf("%lld %lld %lld\n", n, h, t/t2);
        return 0;
      }
    }
  }

  return 0;
}
