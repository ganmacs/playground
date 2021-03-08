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

  int A, B, C, X, Y;
  long long int ans = 12345678987, k;
  cin >> A >> B >> C >> X >> Y;
  int c = 0;

  for (; c <= 2*max(X, Y); c += 2) {
    auto a = max(X - (c/2), 0);
    auto b = max(Y - (c/2), 0);


    k = a*A + b*B + c*C;
    if (k < ans) {
      ans = k;
    }
  }

  cout << ans << endl;
  return 0;
}
