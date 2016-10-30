#include <cstdio>
#include <iostream>
using namespace std;
static const int M = 200000;

int main(int argc, char *argv[])
{
  int v[M];
  int ans = -2000000000, minv, n;

  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];

  minv = v[0];

  for (int i = 1; i < n; i++) {
    ans = max(ans, v[i] - minv);
    minv = min(minv, v[i]);
  }

  cout << ans << endl;
  return 0;
}
