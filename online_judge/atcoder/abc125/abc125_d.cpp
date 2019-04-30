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
  int N;
  long long A[123450], B[123450], C[123450], ans = 0, diff1 = 0, diff2 = 0;

  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int i = 0; i < N-1; i++) {
    B[i] = A[i] + A[i + 1];
    C[i] = -1*A[i] + -1*A[i + 1];

    long long d = C[i]-B[i];
    if (diff1 < d) {
      diff2 = diff1;
      diff1 = d;
    } else if (diff2 < d) {
      diff2 = d;
    }

    ans += B[i];
  }

  cout << ans + diff1 + diff2 << endl;
  return 0;
}
