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

  vector<int> A(N + 1), B(N), A2, B2;

  for (auto& vi: A) {
    cin >> vi;
    A2.push_back(vi);
  };

  for (auto& vi: B) {
    cin >> vi;
    B2.push_back(vi);
  };

  long long int ans1 = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 2; j++) {
      auto k = min(B[i], A[i + j]);
      B[i] -= k;
      A[i + j] -= k;
      ans1 += k;
    }
  }

  // for (auto& vi: A) {
  //   cout << vi << " ";
  // };
  // puts("");
  // for (auto& vi: B) {
  //   cout << vi << " ";
  // };
  // puts("");


  long long int ans2 = 0;
  for (int i = N-1; i >= 0; i--) {
    for (int j = 1; j >= 0; j--) {
      auto k = min(B2[i], A2[i + j]);
      B2[i] -= k;
      A2[i + j] -= k;
      ans2 += k;
    }
  }

  // cout << ans1 << endl;
  // cout << ans2 << endl;
  cout << max(ans2, ans1) << endl;

  return 0;
}
