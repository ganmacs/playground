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
  unsigned long long N;
  int ans = 0;

  cin >> N;

  while (N > 0) {
    unsigned long long v = N%10;

    if ((N / 10) != 0) {
      if (v <= 8) {
        N = N - (v + 1);
      }
      ans += 9;
    } else {
      ans += v;
    }
    N = N / 10;
  }

  cout << ans << endl;
  return 0;
}
