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
  int N;
  cin >> N;
  vector<long long> V(N), S(N);
  for (auto& vi: V) cin >> vi;
  sort(V.begin(), V.end());

  S[0] = V[0];
  for (long long i = 1; i < N; i++) {
    S[i] = S[i-1] + V[i];
  }

  for (long long i = N-2; i >= 0; i--) {
    if (S[i]*2 < V[i + 1]) {
      cout << N - (i + 1)  << endl;
      return 0;
    }
  }

  cout << N << endl;
  return 0;
}
