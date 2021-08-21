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
  vector<long long> V(N);

  for (int i = 0; i < N; i++) {
    cin >> V[i];
    V[i] -= (i + 1);
  }

  sort(V.begin(), V.end());

  long long ans = 0, t;
  if (V.size() % 2 == 1) {
    t = V[V.size()/2];
  } else {
    t = (V[(V.size()-1)/2] + V[V.size()/2])/2;
  }
  for (auto& vi: V) {
    ans += abs(vi - t);
  }
  printf("%lld\n", ans);
  return 0;
}
