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
  unsigned long long int A, B, C, D;
  cin >> A >> B >> C >> D;

  unsigned long long l = lcm(C, D);
  unsigned long long ans = B - (A-1) - (B/C-(A-1)/C) - (B/D-(A-1)/D) + (B/l-(A-1)/l);

  cout << ans << endl;
}
