#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

unsigned long long int INF = 998244353;

int
main()
{
  int N, d;
  cin >> N;
  vector<int> V;
  map<int, int> M;

  for (int i = 0; i < N; i++) {
    cin >> d;
    V.push_back(d);
    M[d]++;
  }

  if (V[0] != 0 || M[0] != 1) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long int ans = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < M[i]; j++) {
      ans = (ans * M[i-1]) % INF;
    }
  }

  cout << ans << endl;

  return 0;
}
