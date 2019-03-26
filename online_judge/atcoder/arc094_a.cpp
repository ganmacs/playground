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
  int a[3];
  cin >> a[0] >> a[1] >> a[2];
  sort(a, a + 3);

  int d1 = a[2] - a[0];
  int d2 = a[2] - a[1];

  long long int ans = 0;
  if (d1 >= 2) {
    ans += (d1 / 2);
    d1 %= 2;
  }

  if (d2 >= 2) {
    ans += (d2 / 2);
    d2 %= 2;
  }

  if (d1 == 0 && d2 == 0) {
    cout << ans << endl;
  } else if (d1 == d2){
    cout << ans + 1 << endl;
  } else {
    cout << ans + 2 << endl;
  }

  return 0;
}
