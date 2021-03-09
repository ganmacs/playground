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

// const int INF = 1e9;

long long as[112345], ans[112345];

int main(int argc, char *argv[])
{
  int N, K;
  cin >> N >> K;

  fill(ans, ans + N + 10, 0);
  for (int i = 0; i < N; i++) {
    cin >> as[i];
  }

  unsigned long long ret = 0;
  for (int i = 0; i <= (N-K); i++) {
    for (int j = 0; j < K; j++) {
      ans[i] += as[i + j];
    }
    ret += ans[i];
  }

  cout << ret << endl;

  return 0;
}
