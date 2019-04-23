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

int main(int argc, char *argv[])
{
  int N;
  cin >> N;
  vector<int> A(N), B(N), C(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];
  for (int i = 0; i < N; i++) cin >> C[i];

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  sort(C.begin(), C.end());

  long long ans = 0;
  for (int i = 0; i < N; i++) {
    long long ai = lower_bound(A.begin(), A.end(), B[i]) - A.begin();
    long long ci = C.end() - upper_bound(C.begin(), C.end(), B[i]);
    ans += ai*ci;
  }

  cout << ans << endl;
  return 0;
}
