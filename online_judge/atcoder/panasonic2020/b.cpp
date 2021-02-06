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

int main(int argc, char *argv[])
{
  long long int A, B;
  cin >> A >> B;

  if (A % 2 == 1 && B%2 == 1) {
    long long int a = ((A-1)*B)/2 + (B/2) + 1;
    cout << a << endl;
  } else {
    cout << (A*B/2) << endl;
  }

  return 0;
}
