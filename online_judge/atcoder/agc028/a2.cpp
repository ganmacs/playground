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
  long long N, M;
  string S, T;
  cin >> N >> M;
  cin >> S >> T;

  long long gg = gcd(N, M);
  for (int i = 0; i < gg; i++) {
    if (S[i*N/gg] != T[i*M/gg]) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << lcm(N, M) << endl;
  return 0;
}
