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
  int N, K, a[100], ans = 0;
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> a[i];
  sort(a, a + N, greater<int>());

  for (int i = 0; i < K; i++) {
    ans += a[i];
  }

  printf("%d\n", ans);
}
