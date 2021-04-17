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
  long long int a, b, x;
  cin >> a >> b >> x;

  if (a%x != 0) {
    a += (x-(a%x));
  }

  if (a > b) {
    cout << 0 << endl;
  } else {
    cout << 1 + (b-a)/x << endl;
  }

  return 0;
}
