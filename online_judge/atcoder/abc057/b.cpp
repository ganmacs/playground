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
  int N, M, a[60], b[60], c[60], d[60];
  cin >> N >> M;

  for (int i = 0; i < N; i++) cin >> a[i] >> b[i];
  for (int i = 0; i < M; i++) cin >> c[i] >> d[i];


  for (int i = 0; i < N; i++) {
    long long v = 1e18;
    int ans = 0;
    for (int j = 0; j < M; j++) {
      long long tmp = abs(a[i]-c[j]) + abs(b[i] - d[j]);
      if (v > tmp) {
        ans = j + 1;
        v = tmp;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
