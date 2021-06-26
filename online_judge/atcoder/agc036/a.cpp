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
  unsigned long long S;
  cin >> S;

  long long d = 1e9;
  long long c = 1;
  long long a = (S + d - 1) / d;
  long long b = a * d - S;
  cout << "0 0 " << a << " " << b << " " << c << " " << d << endl;
  return 0;
}
