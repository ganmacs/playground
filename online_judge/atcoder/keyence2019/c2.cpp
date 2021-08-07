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
  int N;
  cin >> N;
  vector<long long> A(N), B(N);
  long long ab = 0, aa = 0,  bbb = 0;;

  for (auto& vi: A) {
    cin >> vi;
    aa += vi;
  }
  for (auto& vi: B) {
    cin >> vi;
    ab += vi;
  }

  if (aa < ab) {
    printf("%d\n", -1);
    return 0;
  }

  vector<long long> AA;
  long long ans = 0;

  for (int i = 0; i < N; i++) {
    if (A[i] <= B[i]) {
      bbb += (B[i]-A[i]);
      ans++;
    } else {
      AA.push_back(A[i]-B[i]);
    }
  }

  if (bbb == 0) {
    printf("%d\n", 0);
    return 0;
  }

  sort(AA.begin(), AA.end(), greater<long long>());
  for (auto& vi: AA) {
    bbb -= vi;
    ans += 1;

    if (bbb <= 0) {
      break;
    }
  }

  printf("%lld\n", ans);
  return 0;
}
