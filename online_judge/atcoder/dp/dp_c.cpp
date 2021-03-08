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

long long ans[123456][3];
int N, a[123456], b[123456], c[123456];

int main(int argc, char *argv[])
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }

  ans[0][0] = a[0];
  ans[0][1] = b[0];
  ans[0][2] = c[0];

  for (int i = 1; i < N; i++) {
    ans[i][0] = a[i] + max(ans[i-1][1], ans[i-1][2]);
    ans[i][1] = b[i] + max(ans[i-1][0], ans[i-1][2]);
    ans[i][2] = c[i] + max(ans[i-1][1], ans[i-1][0]);
  }

  cout << max(max(ans[N-1][0], ans[N-1][1]), ans[N-1][2]) << endl;
  return 0;
}
