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
  unsigned long long R, X, Y;
  cin >> R >> X >> Y;
  double d = sqrt(pow(X, 2) + pow(Y, 2));
  double k = d/(double)R;

  if (d < R) {
    cout << 2 << endl;
  } else {
    cout << ceil(k) << endl;
  }

  return 0;
}
