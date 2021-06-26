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
  cin >> N >> A >> B;
  vector<int> V(N);
  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }

  long long ans = 0;
  for (int i = 1; i < N; i++) {
    ans += min(B, (V[i] - V[i-1])*A);
  }

  cout << ans << endl;
  return 0;
}
