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
  long long N, A, B;
  cin >> N >> A >> B;

  if (A > B || (N == 1 && B != A)) {
    cout << 0 << endl;
  } else if (A == B) {
    cout << 1 << endl;
  } else {
    cout << (B-A)*(N-2) + 1 << endl;
  }

  return 0;
}
