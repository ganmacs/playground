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
  vector<pair<char, int>> V;
  cin >> N >> K >> S;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;
    V.push_back({ S[i], j-i });
    i = j;
  }

  long long l = 0, ans = 0, tmp = 0, zeroc = 0;
  for (int i = 0; i < V.size(); i++) {
    tmp += V[i].second;
    if (V[i].first == '0') zeroc++;

    while (zeroc > K) {
      tmp -= V[l].second;
      if (V[l].first == '0') zeroc--;
      l++;
    }

    ans = max(tmp, ans);
  }

  printf("%lld\n", ans);
  return 0;
}
