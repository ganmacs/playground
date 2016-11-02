#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define M 100000

long long W[M], n, k;

int cc(long long p) {
  long long sum;
  int j = 0, i;

  for (i = 0; i < k; i++) {
    sum = 0;
    while (sum + W[j] <= p) {
      sum += W[j];
      j++;
      if (j == n) return n;
    }
  }

  return j;
}

int solver()
{
  // max weight * max item
  int l = 0, mid, r = 100000 * 10000 - 1;
  while (l < r) {
    mid = (l + r) / 2;
    int v = cc(mid);            // max n

    if (v >= n) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  return l;
}

int main(int argc, char *argv[])
{
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> W[i];

  cout << solver() << endl;
  return 0;
}
