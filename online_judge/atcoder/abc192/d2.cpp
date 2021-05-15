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
long long M;
int N;

bool check(long long base) {
  vector<long long> Y;
  long long m = M;

  while (m > 0) {
    Y.push_back(m % base);
    m /= base;
  }
  reverse(Y.begin(), Y.end());

  int MY = Y.size();

  if (MY > N) {
    return true;
  } else if (MY < N) {
    return false;
  }

  for (int i = 0; i < N; i++) {
    long long x = X[i] - '0';

    if (x < Y[i]) {
      return true;
    } else if (x > Y[i]) {
      return false;
    }
  }

  return true;
}

int main()
{
  cin >> X >> M;
  N = X.size();
  if (N == 1) {
    if ((X[0]-'0') <= M) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
    return 0;
  }

  long long n = 0;
  for (auto& vi: X) {
    n = max(n, (long long)vi-'0');
  }
  long long ok = n + 1, ng = (long long)1e18 + 1;

  if (!check(ok)) {
    cout << 0 << endl;
    return 0;
  }

  while (abs(ok - ng) > 1) {
    long long p = (ok + ng)/2;
    if (check(p)) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << (ok - n) << endl;
  return 0;
}
