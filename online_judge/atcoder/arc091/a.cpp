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
  unsigned long long N, M;
  cin >> N >> M;

  if (N == 1 && M == 1) {
    cout << 1 << endl;
  } else if (N == 1) {
    cout << M-2 << endl;
  } else if (M == 1) {
    cout << N-2 << endl;
  } else {
    cout << (N-2)*(M-2) << endl;
  }
  return 0;
}
