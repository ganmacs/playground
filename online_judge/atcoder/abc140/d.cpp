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
  int N, K, ans = 0, t = 0;
  cin >> N >> K;
  string S;
  cin >> S;

  for (int i = 0; i + 1< N; i++) if(S[i] != S[i + 1]) t++;
  printf("%d\n", N-1 - max(t-2*K, 0));

  return 0;
}
