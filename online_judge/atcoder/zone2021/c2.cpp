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
  set<int> S;
  for (auto& vi: V) {
    int ii = 0;
    for (int i = 0; i < 5; i++) {
      if (vi[i] >= t) ii |= (1 << i);
    }

    S.insert(ii);
  }

  for (auto& s1: S) {
    for (auto& s2: S) {
      for (auto& s3: S) {
        if ((s1|s2|s3) == 31) {
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
    V.push_back({ a, b, c, d, e });
  }

  long long ok = 1, ng = 1e9 + 1;

  while (abs(ok - ng) > 1) {
    long long m = (ok + ng)/2;

    if (check(m)) {
      ok = m;
    } else {
      ng = m;
    }
  }

  cout << ok << endl;
  return 0;
}
