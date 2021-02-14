#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int
main()
{
  long long int A, B, C;
  int r = 0;

  cin >> A >> B >> C;


  if (A%2 == 0 && A == B && B == C) {
    cout << -1 << endl;
    return 0;
  }


  while (A%2 == 0 && B%2 == 0 && C%2 == 0) {
    r++;
    auto a = A/2;
    auto b = B/2;
    auto c = C/2;

    A = b + c;
    B = c + a;
    C = a + b;

    if (A%2 == 0 && A == B && B == C) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << r << endl;

  return 0;
}
