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
  };


  unsigned long long ans = 1e18;
  for (int i = -100; i <= 100; i++) {
    unsigned long long t = 0;
    for (auto& vi: V) {
      t += pow(vi-i, 2);
    };

    ans = min(ans, t);
  }

  cout << ans << endl;
  return 0;
}
