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
  string S;
  cin >> S;
  vector<int> V(3, 0);
  for (auto& vi: S) {
    V[vi-'a']++;
  }
  sort(V.begin(), V.end());
  V[2] -= V[0];
  V[1] -= V[0];

  if (V[2] >= 2 || V[1] >= 2)  {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }

  return 0;
}
