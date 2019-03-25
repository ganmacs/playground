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

long long solv(int p, long long sum) {
  if (p >= len) return sum;

  int c = 0;
  for (int i = p; i < len; i++) {
    c = c*10 + S[p];
    ans += solv(p + 1, c + sum);
  }

  return ans;
}

int main(int argc, char *argv[])
{
  cin >> S;
  len = S.size();

  printf("%lld\n", solv(0, 0));
  return 0;
}
