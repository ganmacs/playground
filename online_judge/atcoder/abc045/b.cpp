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

  string a, b, c;
  cin >> a >> b >> c;

  char t = 'a';
  int aa = 0, bb = 0, cc = 0;
  while (true) {
    if (t == 'a') {
      if (aa == a.size()) {
        cout << 'A' << endl;
        return 0;
      }

      t = a[aa];
      aa++;
    } else if (t == 'b') {
      if (bb == b.size()) {
        cout << 'B' << endl;
        return 0;
      }

      t = b[bb];
      bb++;
    } else if (t == 'c') {
      if (cc == c.size()) {
        cout << 'C' << endl;
        return 0;
      }

      t = c[cc];
      cc++;
    }
  }

  return 0;
}
