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

int A[112345], B[112345];

int main(int argc, char *argv[])
{
  int Q, l, r;

  fill(A, A + 100000, 0);
  fill(B, B + 100000, 0);

  cin >> Q;

  A[1] = 0;
  A[3] = 1;

  B[1] = 0;
  B[3] = 0;
  B[5] = 1;

  for (int i = 5; i <= 100000; i += 2) {
    bool f = true;
    for (int k = 2; f && k*k <= i; k++) {
      if (i % k == 0) f = false;
    }
    A[i] = (f ? 1 : 0);

    if (f) {
      f = (A[(i + 1)/2] == 1);
    }

    B[i+2] = B[i] + (f ? 1 : 0);
  }

  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    cout << (B[r + 2]-B[l]) << endl;
  }

  return 0;
}
