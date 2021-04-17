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
#include <numeric>

using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;
  vector<int> V(N);
  priority_queue<pair<int, int>> VV;
  for (auto& vi: V) {
    cin >> vi;
  };
  sort(V.begin(), V.end());

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && V[i] == V[j]) {
      j++;
    }

    VV.push(make_pair(V[i], j-i));
    i = j;
  }

  int b, c;
  for (int i = 0; i < M; i++) {
    cin >> b >> c;
    VV.push(make_pair(c, b));
  }

  unsigned long long int ans = 0;
  unsigned long long int rest = N;
  while (!VV.empty() && rest >= 0) {
    auto v = VV.top();
    unsigned long long m = min((unsigned long long)v.second, rest);

    ans += (unsigned long long)v.first * m;
    rest -= min(m, rest);
    VV.pop();
  }

  cout << ans << endl;
  return 0;
}
