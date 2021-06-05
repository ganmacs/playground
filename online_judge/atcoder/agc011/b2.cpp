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

long long d[100001];

int main()
{
  int N;
  cin >> N;
  vector<long long> A(N);
  for (auto& vi: A) cin >> vi;
  sort(A.begin(), A.end());

  d[0] = A[0];
  for (int i = 1; i < N; i++) {
    d[i] = d[i-1] + A[i];
  }

  int ans = 1;
  for (int i = N-2; i >= 0; i--) {
    if (d[i]*2 < A[i + 1]) {
      break;
    }
    ans++;
  }

  cout << ans << endl;
  return 0;
}
