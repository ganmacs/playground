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
  long long N, Q, K;
  cin >> N >> Q;
  vector<long long> A(N), V(N);
  for (auto& vi: A) cin >> vi;

  for (int i = 0; i < N; i++) {
    V[i] = A[i]-(i + 1);
  }

  while (Q--) {
    cin >> K;
    int i = lower_bound(V.begin(), V.end(), K) - V.begin();
    if (i == N) {
      cout << A[N-1] + (K - V[N-1]) << endl;
    } else {
      cout << (A[i]-1) - (V[i] - K) << endl;
    }
  }

  return 0;
}
