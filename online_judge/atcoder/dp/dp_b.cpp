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

int main(int argc, char *argv[])
{
  int N, K, h[100000];
  long long  ans[100000];

  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  ans[0] = 0;
  for (int i = 1; i < N; i++) {
    ans[i] = 1e9;
    for (int j = 1; j <= K && j <= i; j++) {
      ans[i] = min(ans[i], ans[i-j] + abs(h[i-j] - h[i]));
    }
  }

  cout << ans[N-1] << endl;
}
