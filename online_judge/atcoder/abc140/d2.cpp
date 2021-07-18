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
#include <algorithm>

using namespace std;

int main()
{
  long long N, K, a = 0;
  string S;
  cin >> N >> K >> S;

  for (int i = 0; i + 1 < N; i++) {
    if(S[i] != S[i + 1]) a++;
  }

  printf("%lld\n", N - 1 - max((a - 2*K), 0LL));
  return 0;
}
