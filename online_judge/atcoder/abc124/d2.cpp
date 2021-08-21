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
  int N, K;
  string S;
  cin >> N >> K >> S;

  vector<pair<char, int>> V;
  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;
    V.push_back({ S[i], j-i});
    i = j;
  }

  long long ans = 0, t = 0;
  int l = 0, z = 0;
  for (int i = 0; i < V.size(); i++) {
    t += V[i].second;
    if (V[i].first == '0') z++;

    while (z > K) {
      t -= V[l].second;
      if (V[l].first == '0') z--;
      l++;
    }

    ans = max(ans, t);
  }

  printf("%lld\n", ans);
  return 0;
}
