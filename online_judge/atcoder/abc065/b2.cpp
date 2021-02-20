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

int main(int argc, char *argv[])
{

  int N, a[1234567];

  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> a[i];
  }

  int i = 1, j = 0;
  while (i != 2) {
    if (a[i] == -1) {
      cout << -1 << endl;
      return 0;
    }

    j++;
    auto k = i;
    i = a[i];
    if (i == 2) {
      break;
    }

    a[k] = -1;
  }

  cout << j << endl;
  return 0;

}
