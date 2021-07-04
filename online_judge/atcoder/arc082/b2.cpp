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
  int ans = 0;
  vector<int> p(N);
  for (auto& vi: p) cin >> vi;


  for (int i = 0; i < N; i++) {
    if (p[i] == (i + 1)) {
      ans++;
      if (i + 1 < N) {
        swap(p[i], p[i + 1]);
      } else {
        swap(p[i], p[i - 1]);
      }
    }
  }

  cout << ans << endl;

  return 0;
}
