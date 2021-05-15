#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <numeric>

using namespace std;
vector<array<int, 5>> V;

bool check(long long t) {
  set<int> A;

  for (auto& vi: V) {
    int v = 0;
    for (int i = 0; i < 5; i++) {
      if (t <= vi[i]) {
        v |= (1 << i);
      }
    }
    A.insert(v);
  }

  for (auto& v1: A) {
    for (auto& v2: A) {
      for (auto& v3: A) {
        if ((v1|v2|v3) == 31) {
          return true;
        }
      }
    }
  }

  return false;
}

int main()
{
  int N, a, b, c, d, e;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a >> b >> c >> d >> e;
    V.push_back({a, b, c, d, e});
  }

  long long ok = 1, ng = 1e9 + 1;

  while (abs(ok-ng)>1) {
    long long p = (ok + ng)/2;
    if (check(p)) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << ok << endl;
  return 0;
}
