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

int
main()
{
  string S;
  long long K;
  vector<pair<char, long long>> V;
  cin >> S >> K;
  int N = S.length();
  unsigned long long int ans = 0;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && S[i] == S[j]) j++;
    V.push_back(make_pair(S[i], j-i));
    ans += (j-i)/2;
    i = j;
  }
  ans *= K;

  if (V.size() == 1) {
    cout << (N*K)/2  << endl;
    return 0;
  } else if (V[0].first == V[V.size()-1].first) {
    if ((V[0].second + V[V.size()-1].second) % 2 == 0) {
      ans += K-1;
    }
  }

  cout << ans << endl;

  return 0;
}
