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

int main()
{
  int N;
  cin >> N;
  vector<vector<int> > V(10, vector(10, 0));

  for (int i = 1; i <= N; i++) {
    int j = i;
    vector<int> v;
    while (j) {
      v.push_back(j%10);
      j /= 10;
    }

    int l = v[0], r = v.back();
    if (l == 0||r == 0) continue;

    V[l][r]++;
  }

  long long ans = 0;

  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < 10; j++) {
      ans += V[i][j]*V[j][i];
    }
  }
  printf("%lld\n", ans);

  return 0;
}
