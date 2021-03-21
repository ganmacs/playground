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
  int N, vi, a4 = 0, a2 = 0, a0 = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> vi;
    if (vi % 4 == 0) {
      a4++;
    }else if (vi % 2 == 0) {
      a2++;
    } else {
      a0++;
    }
  };

  if (a2 == 0) {
    cout << ((a0 <= a4 + 1) ? "Yes" : "No");
  } else {
    cout << ((a0 <= a4) ? "Yes" : "No");
  }

  return 0;
}
