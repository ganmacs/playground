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

const int L = 1e9 + 7;

int main()
{

  int N;
  string S;
  map<char, int> M;
  cin >> N >> S;

  for (int i = 0; i < N; i++) {
    M[S[i]- '0']++;
  }

  long long ans = 1;
  for (auto& vi: M) {
    ans *= (vi.second + 1);
    ans %= L;
  };

  cout << ans -1 << endl;
  return 0;
}
