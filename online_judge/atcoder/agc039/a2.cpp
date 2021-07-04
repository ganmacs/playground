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
  long long K;
  cin >> S >> K;
  long long N = S.size();
  long long ans = 0;
  vector<pair<char, long long>> V;

  for (long long i = 0; i < N;) {
    long long j = i;
    while (j<N && S[i] == S[j]) j++;
    V.push_back({S[i], j-i});
    ans += ((j-i)/2)*K;
    i = j;
  }


  if (V.size() == 1) {
    cout << (V[0].second*K)/2 << endl;
    return 0;
  }

  if (S[0] == S.back()) {
    ans -= (V[0].second/2)*K;
    ans -= (V.back().second/2)*K;
    ans += (V[0].second/2) + ((V.back().second + V[0].second)/2)*(K-1) + (V.back().second/2);
  }

  cout << ans << endl;
  return 0;
}
