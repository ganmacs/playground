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
  int N = S.length();
  int d[3] = {0, 0, 0};

  for (auto& vi: S) {
    d[vi-'a']++;
  };

  sort(d, d + 3);
  for (int i = 2; i >= 0; i--) {
    d[i] -= d[0];
  }

  cout << (d[2] >= 2 ? "NO" : "YES") << endl;
  return 0;
}
