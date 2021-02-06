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
  long long a, b, x, ans = 0;
  cin >> a >> b >> x;

  long long vv = (a / x);
  if (a % x == 0) vv -= 1;
  long long v2 = (b / x);

  cout << v2 - vv << endl;
  return 0;
}
