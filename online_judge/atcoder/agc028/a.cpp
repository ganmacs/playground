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

int
main()
{
  long long N, M;
  cin >> N >> M;
  string S, T;
  cin >> S >> T;

  long long g = gcd(N, M);
  for (int i = 0; i < g; i++) {
    if (S[i*N/g] != T[i*M/g]) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << lcm(N, M) << endl;
  return 0;
}
