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
  vector<vector<long long>>  M(11, vector(11, 0LL));

  for (int i = 1; i <= N; i++) {
    vector<int> V;
    int j = i;
    while (j >= 1) {
      V.push_back(j % 10);
      j /= 10;
    }
    if (V[0] == 0 || V.back() == 0) continue;
    M[V[0]][V.back()]++;
  }

  long long ans = 0;
  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < 10; j++) {
      ans += M[i][j] * M[j][i];
    }
  }

  printf("%lld\n", ans);
  return 0;
}
