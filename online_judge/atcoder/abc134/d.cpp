#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int d[212345];

int main()
{
  int N;
  cin >> N;
  vector<int> V(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> V[i];
  }

  for (int i = N; i >= 1; i--) {
    int sum = V[i];
    for (int j = i*2; j <= N; j += i) sum += d[j];
    d[i] = (sum % 2);
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    if(d[i]) ans++;
  }

  printf("%d\n", ans);
  for (int i = 1; i <= N; i++) {
    if(d[i]) printf("%d\n", i);
  }

  return 0;
}
