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

bool f(string x, long long unsigned int m, int base) {
  long long unsigned int b = 1;
  long long unsigned int g = 0;
  for (int i = x.length()-1; i >= 0; i--) {
    g += (x[i]-'0') * b;
    b *= base;
  }

  return m >= g;
}

string X;
int MV[70];

bool f2(long long unsigned int x, int base) {
  auto N = 0;
  while (x > 0) {
    MV[N] = x % base;
    x = (x - MV[N]) / base;
    N++;
  }

  // for (int i = N-1; i >= 0; i--) {
  //   printf("%d ", MV[i]);
  // }
  // printf("\n");

  if (X.length() > N) {
    return false;
  } else if (X.length() < N) {
    return true;
  }

  for (int i = 0;i < N; i++) {
    if (X[i]-'0' == MV[N-(i+1)]) {
      continue;
    }

    return (X[i]-'0' < MV[N-(i+1)]);
  }

  return true;
}


int main(int argc, char *argv[])
{
  long long unsigned int M;
  cin >> X >> M;

  int r = 0;
  for (int i = 0; i < X.length(); i++) {
    r = max(r, X[i] - '0');
  }

  long long int l = r + 1;
  long long int rr = 987654000;

  while (rr -l > 1) {
    long long int p = (l + rr) / 2;

    bool ok = f2(M, p);
    if (ok) {
      l = p;
    } else {
      r = p;
    }
  }

  cout << (p - r) << endl;

  return 0;
}
