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
  long long A, B, N;
  cin >> N >> A >> B;
  if (B < A || (N == 1 && B != A)) {
    cout << 0 << endl;
    return 0;
  } else if (N == 1 && B == A) {
    cout << 1 << endl;
    return 0;
  }

  cout << ((B-A)*(N-2) + 1) << endl;
  return 0;
}
