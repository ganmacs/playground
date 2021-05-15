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

int main()
{
  long long ans = 0;
  int N;
  cin >> N;
  vector<long long> A(N), B(N);
  vector<long long> V;
  for (auto& vi: A) cin >> vi;
  for (auto& vi: B) cin >> vi;

  long long sum = 0;
  for (int i = 0; i < N; i++) {
    if (B[i] < A[i]) {
      V.push_back(B[i] - A[i]);
    } else if (B[i] > A[i]) {
      sum += B[i] - A[i];
      ans++;
    }
  }

  if (sum == 0) {
    cout << 0 << endl;
    return 0;
  }

  sort(V.begin(), V.end());
  long long t = 0;
  for (auto& vi: V) {
    t += -vi;
    ans++;

    if (t >= sum) {
      break;
    }
  };

  if (t < sum) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }
  return 0;
}
