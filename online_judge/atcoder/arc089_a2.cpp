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

string S;
int len;
long long ans = 0;

int main(int argc, char *argv[])
{
  int N, t[123456], x[123456], y[123456];
  cin >> N;

  t[0] = x[0] = y[0] = 0;
  for (int i = 1; i <= N; i++) {
    cin >> t[i] >> x[i] >> y[i];
  }

  for (int i = 0; i < N; i++) {
    int d = t[i + 1] - t[i];
    int dist = abs(x[i+1]-x[i]) + abs(y[i+1]-y[i]);
    if (d < dist || d%2 != dist%2) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
  return 0;
}
