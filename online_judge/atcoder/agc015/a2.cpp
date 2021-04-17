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

  if (A > B || (N == 1 && (B - A) > 1)) {
    cout << 0 << endl;
  } else if (B == A) {
    cout << 1 << endl;
  } else {
    long l = (N-1)*A + B;
    long r = A + (N-1)*B;
    cout << (r-l+1) << endl;
  }

  return 0;
}
