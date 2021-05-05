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

vector<array<int, 5>> A;

bool check(int n) {
  set<int> s;

  for (auto& ai: A) {
    int bit = 0;
    for (auto& vi: ai) {
      bit <<= 1;
      bit |= (vi >= n);
    };
    s.insert(bit);
  };

  for (auto& a1: s) {
    for (auto& a2: s) {
      for (auto& a3: s) {
        if ((a1|a2|a3) == 31) {
          return 1;
        }
      };
    };
  };

  return false;
}

int main()
{

  int N, a, b, c, d, e;
  cin >> N;

  for (int i = 0; i < N; i++) {
    auto v = array<int, 5>{};
    for (auto& vi: v) {
      cin >> vi;
    };
    A.push_back(v);
  }

  int ok = 0, ng = 1e9 + 1;

  while (abs(ok - ng) > 1) {
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
