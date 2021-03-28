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
#include <numeric>

using namespace std;

int main()
{
  int N, X;
  cin >> N >> X;

  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };
  V.push_back(X);
  sort(V.begin(), V.end());

  int v = V[1] - V[0];
  if (N > 1) {
    for (int i = 2; i < V.size(); i++) {
      v = gcd(v,  V[i] - V[i-1]);
    }
  }

  cout << v << endl;
  return 0;
}
