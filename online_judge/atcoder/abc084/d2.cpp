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

int d[112345];
map<int, int> dd;

int ss(int k) {
  for (int i = 2; i*i <= k; i++) {
    if (k % i == 0) {
      dd[k] = 0;
      return 0;
    }
  }
  dd[k] = 1;

  return dd[(k + 1) / 2];
}

int main()
{
  int Q;
  cin >> Q;

  fill(d, d + 3, 0);
  dd[2] = 1;
  for (int i = 3; i <= 100000; i += 2) {
    d[i] = d[i-2] + ss(i);
  }

  int l, r;
  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    cout << (d[r] - d[l-2]) << endl;
  }

  return 0;
}
