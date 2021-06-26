#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N;
  cin >> N;

  long long t = 0;

  for (int i = 1; i < max(N, 100); i++) {
    t += i;

    if (t >= N) {
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}
