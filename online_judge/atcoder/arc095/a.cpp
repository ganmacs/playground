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

  vector<int> V2 = V;
  sort(V.begin(), V.end());

  int l = V.size()/2 - 1;
  int r = l + 1;
  double p = (V[l] + V[r])/2.0;

  for (auto& vi: V2) {
    if (vi > p) {
      cout << V[l] << endl;
    } else {
      cout << V[r] << endl;
    }
  };

  return 0;
}
