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

vector<long long> PP(1, 1), V(1, 1);
long long dfs(long long n, long long x)
{
  if (n == 0) {
    if (x <= 0)return 0;
    return 1;
  }

  if (V[n-1] + 2 <= x) {
    return (PP[n-1] + 1) + dfs(n-1, x - (V[n-1] + 2));
  } else if (V[n-1] + 1 == x) {
    return PP[n-1];
  } else {
    return dfs(n-1, x-1);
  }
}

int main()
{
  long long N, X;
  cin >> N >> X;

  for (int i = 1; i <= N; i++) {
    V.push_back(2*V[i-1] + 3);
    PP.push_back(2*PP[i-1] + 1);
  }

  cout << dfs(N, X) << endl;
  return 0;
}
