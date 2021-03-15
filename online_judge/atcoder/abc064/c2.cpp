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

  int d[8], o = 0;
  fill(d, d + 8, 0);

  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };

  for (auto& vi: V) {
    if (vi < 400) {
      d[0]++;
    } else if (vi < 800) {
      d[1]++;
    } else if (vi < 1200) {
      d[2]++;
    } else if (vi < 1600) {
      d[3]++;
    } else if (vi < 2000) {
      d[4]++;
    } else if (vi < 2400) {
      d[5]++;
    } else if (vi < 2800) {
      d[6]++;
    } else if (vi < 3200) {
      d[7]++;
    } else {
      o++;
    }
  };

  int v = 0;
  for (int i = 0; i < 8; i++) {
    if (d[i]) v++;
  }

  cout << max(v, 1) << " " << (v + o) << endl;
  return 0;
}
