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
  int X;
  long long A = 0;
  cin >> X;

  for (int i = 1; i <= X; i++) {
    A += i;
    if (X <= A) {
      cout << i << endl;
      return 0;
    }
  }

  return 0;
}
