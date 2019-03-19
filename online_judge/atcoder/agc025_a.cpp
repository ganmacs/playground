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

int cal(int v) {
  int ret = 0;
  while (v > 0) {
    ret += (v%10);
    v /= 10;
  }
  return ret;
}

int main(int argc, char *argv[])
{
  int N, ans = 1000000;
  cin >> N;

  for (int i = 1; i < N; i++) {
    ans = min(ans, cal(i) + cal(N-i));
  }

  printf("%d\n", ans);
}
