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

vector<long long> V;

void f(long long v)
{
  for (long long i = 1; i*i <= v; i++) {
    if (v % i != 0) continue;

    V.push_back(i);
    long long k = v / i;
    if (i != k) {
      V.push_back(k);
    }
  }
}

int main()
{
  long long N, M, ans = 1;
  cin >> N >> M;

  f(M);
  for (auto& vi: V) {
    if ((M/vi) >= N) {
      ans = max(ans, vi);
    }
  }

  cout << ans << endl;
  return 0;
}
