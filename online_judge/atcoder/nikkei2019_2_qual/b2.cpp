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

unsigned long long int M = 998244353;
unsigned long long int V[112345];

int
main()
{
  int N, mm = 0;
  cin >> N;
  vector<int> V2(N);
  fill(V, V + 112333, 0);
  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    V2[i] = a;
    V[a]++;
    mm = max(mm, a);
  }

  if (V[0] != 1|| V2[0] != 0) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long int ans = 1;
  for (int i = 1; i <= mm; i++) {
    for (int j = 0; j < V[i]; j++)
      ans = (ans * V[i-1])%M;
  }

  cout << (ans % M) << endl;
  return 0;
}
