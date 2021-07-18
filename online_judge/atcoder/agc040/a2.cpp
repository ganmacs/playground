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
  string S;
  cin >> S;
  int N = S.size();
  vector<pair<char, long long>>  V;
  long long ans = 0;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;
    long long t = j-i;
    ans += (t+1)*t/2;
    V.push_back({S[i], j-i});
    i = j;
  }

  for (int i = 0; i + 1 < V.size(); i++) {
    if (V[i].first == '<') {
      ans -= min(V[i].second,  V[i + 1].second);
    }
  }

  cout << ans << endl;

  return 0;
}
