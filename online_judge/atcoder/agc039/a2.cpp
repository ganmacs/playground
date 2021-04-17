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
  string S;
  unsigned long long K;
  cin >> S >> K;
  int N = S.length();
  vector<pair<char, unsigned long long>> V;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] && S[j] == S[i]) j++;
    V.push_back(make_pair(S[i], j-i));
    i = j;
  }

  unsigned long long ans = 0;
  for (auto& vi: V) {
    ans += (vi.second/2);
  };
  ans *= K;

  if (V.size() == 1) {
    ans = (K*V[0].second)/2;
  } else if (S.length() >= 2 && V[0].first == V[V.size()-1].first) {
    ans += ((V[0].second + V[V.size()-1].second)/2)*(K-1);
    ans -= (V[0].second/2)*(K-1);
    ans -= (V[V.size()-1].second/2)*(K-1);
  }

  cout << ans << endl;
  return 0;
}
