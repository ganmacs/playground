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

string S;
int len;
long long ans = 0;

long long dfs(int p, long long a, long long b) {
  if (len <= p) {
    ans += (a + b);
    return 0;
  }


  dfs(p + 1, (S[p]-'0')+10*a, b);
  dfs(p + 1, S[p]-'0', a+b);
}

int main(int argc, char *argv[])
{
  cin >> S;
  len = S.size();
  dfs(1, S[0]-'0', 0);
  printf("%lld\n", ans);
  return 0;
}
