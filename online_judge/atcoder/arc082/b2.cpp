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
  int N, a, ans = 0;
  cin >> N;
  vector<int> V(N);

  for (auto& vi: V) {
    cin >> vi;
    vi--;
  };

  for (int i = 0; i < N;) {
    if (V[i] == i) {
      int j = i;
      while (j < N && V[j] == j) j++;

      int v = j-i;
      if (v > 0) {
        ans += v/2 + (v % 2);
      }
      i = j;
    } else {
      i++;
    }
  }

  cout << ans << endl;
  return 0;
}
