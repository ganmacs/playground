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
#include <algorithm>

using namespace std;

int main()
{
  int N, K;
  string S;
  cin >> N >> K >> S;
  vector<pair<char, int >> V;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;
    V.push_back({S[i], j - i});
    i = j;
  }

  int ans = 0, ta = 0, zeroc = 0, L = 0;
  for (int i = 0; i < V.size(); i++) {
    ta += V[i].second;
    if (V[i].first == '0') zeroc++;

    while (zeroc > K) {
      ta -= V[L].second;
      if (V[L].first == '0') zeroc--;
      L++;
    }

    ans = max(ans, ta);
  }

  printf("%d\n", ans);

  return 0;
}
