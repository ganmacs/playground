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
  sort(T, T + N, greater<int>());

  int ans = 0;
  int i = 0;
  while (i < N) {
    int sumv = 0;
    long long t = max(T[i] - K, 0LL);
    printf("a %d %lld\n",i , T[i]);

    while (i + 1 < N && T[i + 1] >= t && sumv < C) {
      i++;
      sumv++;
    }
    printf("b %d %d\n", i, sumv);

    if (sumv == 0) i++;
    ans++;
  }

  printf("%d\n", ans);
  return 0;
}
