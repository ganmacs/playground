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

int d[112345];

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  d[0] = 0;
  for (int i = 0; i < N-1; i++) {
    d[i + 1] = V[i + 1] - V[i];
  }

  for (int i = N-1; i >= 1; i--) {
    if (d[i] == -1) {
      d[i]++;
      d[i-1]--;
    }

    if (d[i] < 0) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
