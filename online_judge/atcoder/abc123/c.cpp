#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
  long long N, a[5];
  long long ans = 0;
  cin >> N;
  for (int i = 0; i < 5; i++) {
    cin >> a[i];
  }

  sort(a, a + 5);
  if (N <= a[0]) {
    cout << 5 << endl;
  } else {
    long long r = N - a[0];
    long long vv = r / a[0];
    long long vvv = 0;
    vvv = ((r % a[0]) != 0) ? 1LL : 0LL;
    cout << (5LL + vv + vvv) << endl;
  }
}
