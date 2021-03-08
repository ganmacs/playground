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

long long L[112345], R[112345], k[112345], a[112345];

int main(int argc, char *argv[])
{
  long long Q;
  for (int i = 0; i < Q; i++) {
    cin >> L[i] >> R[i];
  }

  long long lim = 100001;
  for (int i = 1; i < lim; i += 2) {
    if (((i + 1)/2) % 2 == 1) {
      k[i] = 1;
    } else {
      k[i] = 0;
    }
  }

  a[0] = 0;
  a[1] = 0;
  for (int i = 1; i < lim; i += 2) {
    if (k[i] == 1) {
      k[i+1] = k[i-1]++;
    } else {
      k[i+1] = k[i-1];
    }
  }

  return 0;
}
