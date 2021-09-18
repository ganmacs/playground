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
  int N, ans = 0;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) cin >> vi;

  for (int i = N-1; i > 0; i--) {
    if (V[i] == i + 1) {
      swap(V[i], V[i-1]);
      ans++;
    }
  }

  if (V[0] == 1) {
    ans++;
  }

  printf("%d\n", ans);
  return 0;
}
