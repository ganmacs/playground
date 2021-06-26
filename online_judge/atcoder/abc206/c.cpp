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
  vector<int> A(N);
  map<int, long long> M, M2;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    M[A[i]]++;
  }

  int n = N;
  for (auto& vi: M) {
    M2[vi.first] = (n - vi.second)*vi.second;
    n -= vi.second;
  }

  long long ans = 0;
  for (auto& vi: M2) {
    ans += vi.second;
  }

  cout << ans << endl;

  return 0;
}
