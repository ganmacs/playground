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
  unsigned long long int ans = 0;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    ans += (vi-1);
  };

  cout << ans << endl;
  return 0;
}
