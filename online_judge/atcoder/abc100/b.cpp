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
  int D, N, j = 0;
  cin >> D >> N;
  int v =  pow(100, D);
  for (int i = 1; i <= 10000; i++) {
    if ((i % 100) != 0) {
      j++;
    }

    if (j == N) {
      cout << i*v << endl;
      return 0;
    }
  }

  return 0;
}
