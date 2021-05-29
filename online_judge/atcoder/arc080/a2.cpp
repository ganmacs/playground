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
  int N, a0 = 0, a2 = 0, a4 = 0;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
    if (vi % 4 == 0) {
      a4++;
    } else if (vi % 2 == 0) {
      a2++;
    } else {
      a0++;
    }
  }

  if ((a4 + a2) == 0) {
    cout << "No" << endl;
    return 0;
  }

  if (a2 > 0) {
    if (a0 > a4) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  } else {
    if (a0 - 1 > a4) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }

  return 0;
}
