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
  long long X, Y;
  cin >> X >> Y;

  long long ans = 1;
  long long aa = X;

  while (true) {
    aa *= 2;
    if (aa > Y) break;
    ans++;
  }

  cout << ans << endl;
  return 0;
}
