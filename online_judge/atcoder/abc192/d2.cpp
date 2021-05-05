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

string X;
unsigned long long M;
int N;

bool fa(long long base) {
  unsigned long long int v = 0;
  for (int i = 0; i < N; i++) {
    if ((pow(base, N-i-1) * (long long )(X[i]-'0')) > M) {
      return false;
    }

    v += pow(base, N-i-1) * (long long)(X[i]-'0');
    if (v > M) {
      return false;
    }
  }

  return true;
}

int main()
{
  cin >> X >> M;
  N = X.size();
  long long ma = 0;

  if (N == 1) {
    if ((X[0] - '0') <= M) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
    return 0;
  }

  for (long long i = 0; i < N; i++) {
    ma = max(ma, (long long) X[i]-'0');
  }

  long long ok = ma + 1;
  long long ng = M + 1;

  // To check ok is really ok.
  if (!fa(ok)) {
    cout << 0 << endl;
    return 0;
  }

  while (abs(ok - ng) > 1) {
    long long p = (ok + ng)/2;
    if (fa(p)) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << (ok-(ma + 1) + 1) << endl;

  return 0;
}
