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
  int N, Q;
  cin >> N >> Q;
  vector<long long> A(N), B(N);
  for (auto& vi: A) cin >> vi;

  for (int i = 0; i < N; i++) {
    B[i] = A[i] - (i + 1);
  }

  long long K;
  for (int k = 0; k < Q; k++) {
    cin >> K;
    int i = lower_bound(B.begin(), B.end(), K) - B.begin();

    if (i == B.size()) {
      cout << A[i-1] + (K-B[i-1]) << endl;
    } else {
      cout << A[i]- (B[i]-K + 1) << endl;
    }
  }

  return 0;
}
