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
  vector<pair<char, long long>> V;
  unsigned long long ans = 0;
  cin >> S >> K;
  int N;
  N = S.size();

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;

    V.push_back(make_pair(S[i], j-i));
    ans += ((j-i)/2)*K;
    i = j;
  }

  if (V.size() == 1) {
    cout << (K*V[0].second)/2 << endl;
    return 0;
  }

  if (V.front().first == V.back().first) {
    if ((V.back().second % 2) == 1 && (V.front().second) % 2 == 1) {
      ans += (K-1);
    }
  }

  cout << ans << endl;
  return 0;
}
