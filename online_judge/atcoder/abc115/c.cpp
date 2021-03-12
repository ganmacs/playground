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

long long h[112345];

int main(int argc, char *argv[])
{
  int N, K;

  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  sort(h, h + N);
  long long ans = 1e9;
  for (int i = 0; i < (N-K+1); i++) {
    ans = min(ans, h[i+K-1] - h[i]);
  }

  cout << ans << endl;
  return 0;
}
