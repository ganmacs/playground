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
  long unsigned long int A, B;
  cin >> A >> B;

  if (A == 1 || B == 1) {
    cout << 1 << endl;
    return 0;
  } else if ((A % 2 == 1) && (B % 2 == 1)) {
    cout << A*B/2+1 << endl;
  } else {
    cout << (A*B/2) << endl;
  }

  return 0;
}
