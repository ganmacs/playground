#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<long long> A(N), B(N), C(N);
  int a;
  map<long long , long long > A2, B2;
  for (auto& vi: A) {
    cin >> a;
    A2[a]++;
  }
  for (auto& vi: B) {
    cin >> vi;
    B2[vi]++;
  }
  for (auto& vi: C) cin >> vi;

  map<long long , long long > D;
  for (auto& vi: C) {
    D[B[vi-1]]++;
  }

  unsigned long long ans = 0;
  for (auto& vi: A2) {
    ans += (D[vi.first] * vi.second);
  }

  cout << ans << endl;
  return 0;
}
