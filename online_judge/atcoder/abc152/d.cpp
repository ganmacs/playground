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
  vector<vector<int>> V(10, vector(10, 0));

  for (int i = 1; i <= N; i++) {
    int nn = i;
    vector<int> t;
    while (nn) {
      t.push_back(nn%10);
      nn /= 10;
    }

    int a = t[0], b = t.back();
    if (a == 0 || b == 0) continue;
    V[a][b]++;
  }

  long long ans = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ans += V[i][j] * V[j][i];
    }
  }

  cout << ans << endl;
  return 0;
}
