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
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    vi--;
  };

  long long ans = 0;

  for (int i = 0; i < N; i++) {
    if (V[i] == i) {
      if ((i - 1) >= 0) {
        swap(V[i],  V[i-1]);
      } else {
        swap(V[i], V[i + 1]);
      }
      ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
