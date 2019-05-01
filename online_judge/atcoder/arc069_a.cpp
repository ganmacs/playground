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
  long long N, M;
  cin >> N >> M;

  if (M % 2 == 1) M -= 1;

  if (M == 0) {
    cout << 0 << endl;
  } else if (M >= 2*N) {
    long long v = M - (2 * N);
    cout << (v / 4) + N << endl;
  } else {
    cout << M / 2 << endl;
  }

  return 0;
}
