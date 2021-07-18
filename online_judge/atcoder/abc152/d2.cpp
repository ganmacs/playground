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
  long long ans = 0;
  map<int, map<int, long long>> M;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    int j = i;
    vector<int> v;
    while (j) {
      v.push_back(j%10);
      j /= 10;
    }
    int l = v.front(), r = v.back();
    if (l == 0 || r == 0) continue;
    M[l][r]++;
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ans += (M[i][j]*M[j][i]);
    }
  }

  printf("%lld\n", ans);
}
