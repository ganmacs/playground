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
  long long A, B, ans = 0;
  cin >> A >> B;

  long long t = gcd(A, B);

  vector<int> V;
  int j = 2;
  if (t > 0) V.push_back(1);
  while (t > 1) {
    if (t % j == 0) V.push_back(j);
    while (t % j == 0) t /= j;
    j++;
  }

  printf("%ld\n", V.size());
  return 0;
}
