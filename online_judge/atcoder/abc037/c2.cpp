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

unsigned long long ans[112345];

int main(int argc, char *argv[])
{
  int N, K;
  long long a;
  cin >> N >> K;

  fill(ans, ans + N + 10, 0);
  for (int i = 0; i < N; i++) {
    cin >> a;
    ans[i + 1] = ans[i] + a;
  }

  unsigned long long ret = 0;
  for (int i = K; i <= N; i++) {
    ret += (ans[i] - ans[i-K]);
  }

  cout << ret << endl;
  return 0;
}
