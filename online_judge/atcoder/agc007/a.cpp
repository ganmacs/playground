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

  int H, W;
  cin >> H >> W;
  string a[10];
  int r = 0;

  for (int k = 0; k < H; k++) {
    cin >> a[k];
  }

  for (int k = 0; k < H; k++) {
    bool f = false;
    for (int i = 0; i < W;) {
      if (a[k][i] == '#') {
        if (r != i || f) {
          cout << "Impossible" << endl;
          return 0;
        }

        int j = i;
        while (i < W && a[k][j] == a[k][i]) j++;
        f = true;
        r = (j-1);
        i = j;
      } else {
        i++;
      }
    }
  }

  cout << "Possible" << endl;
  return 0;
}
