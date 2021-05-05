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
  long long N, M, ans = 0;
  cin >> N >> M;

  long long v = (1LL << M);

  cout << v * (1900LL * M + 100LL * (N-M)) << endl;
  return 0;
}
