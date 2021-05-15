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

unsigned long long A, B, X;
bool check(int n) {
  return X >= (A*n + B*to_string(n).size());
}

int main()
{
  cin >> A >> B >> X;
  if (!check(1)) {
    cout << 0 << endl;
    return 0;
  }

  long long ok = 1, ng = 1e9 + 10;

  while (abs(ok - ng) > 1) {
    long long p = (ok + ng)/2;
    if (check(p)) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << min(ok, (long long)1e9) << endl;
  return 0;
}
