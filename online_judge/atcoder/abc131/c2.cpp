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
  unsigned long long A, B, C, D;
  cin >> A >> B >> C >> D;

  A--;
  unsigned long long a = A - (A / C) - (A / D) + (A / lcm(C, D));
  unsigned long long b = B - (B / C) - (B / D) + (B / lcm(C, D));
  cout << b-a << endl;
}
