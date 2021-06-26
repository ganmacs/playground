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
  long long N, A, B;
  long long ans = 0;
  cin >> N >> A >> B;
  vector<long long> X(N);
  for (auto& vi: X) cin >> vi;

  for (int i = 1; i < N; i++) {
    ans += min((X[i] - X[i-1])*A, B);
  }

  cout << ans << endl;
  return 0;
}
