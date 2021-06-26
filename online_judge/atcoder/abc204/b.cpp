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
  int N;
  cin >> N;
  vector<int> V(N);
  unsigned long long ans = 0;

  for (auto& vi: V) {
    cin >> vi;
    if (vi > 10) {
      ans += vi-10;
    }
  }

  cout << ans << endl;
  return 0;
}
