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
  long long N, C, K, T[200000];
  cin >> N >> C >> K;
  for (int i = 0; i < N; i++) {
    cin >> T[i];
  }
  sort(T, T + N);

  int ans = 0, away = -1, cnt = 0;
  for (int i = 0; i < N; i++) {
    if (cnt == C || away < T[i]) {
      ans++;
      cnt = 1;
      away = T[i] + K;
    } else {
      cnt++;
    }
  }

  printf("%d\n", ans);
  return 0;
}
