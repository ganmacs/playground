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
int N;

bool check(int an) {
  set<int> s;

  for (auto& vi: V) {
    int bit = 0;

    for (auto& vii: vi) {
      bit <<= 1;
      bit |= (vii >= an);
    };
    s.insert(bit);
  };

  for (auto& v1: s) {
    for (auto& v2: s) {
      for (auto& v3: s) {
        if ((v1|v2|v3) == 31) return true;
      };
    };
  };

  return false;
}

int main()
{
  int a, b, c, d, e;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b >> c >> d >> e;
    V.push_back({a, b, c, d, e});
  }

  int ok = 1, ng = 1e9 + 1;

  while (abs(ok-ng) > 1) {
    int p = (ok + ng)/2;

    if (check(p)) {
      ok = p;
    } else {
      ng = p;
    }
  }

  cout << ok << endl;
  return 0;
}
