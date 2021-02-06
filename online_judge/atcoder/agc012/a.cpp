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
  long int N, a[1000000];
  long long int ans = 0;
  cin >> N;

  for (int i = 0; i < N*3; i++) cin >> a[i];
  sort(a, a + N*3, greater<int>());
  for (int i = 1; i < N*2; i += 2) ans += a[i];
  printf("%lld\n", ans);
}
