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
  long long int A, B, C;
  cin >> A >> B >> C;
  if (A % 2 == 0 || B % 2 == 0 || C % 2 == 0) {
    cout << 0 << endl;
  } else {
    cout << min(A*B, min(B*C, C*A)) << endl;
  }

  return 0;
}
