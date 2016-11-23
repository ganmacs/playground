#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int MAX = 1000000007;

int main(){
  unsigned long long int x, y, ans = 1;
  cin >> x >> y;

  while (y > 0) {
    if (y % 2 == 1) ans = (ans * x) % MAX;
    y /= 2;
    x = (x * x) % MAX;
  }

  cout << ans << endl;
}
