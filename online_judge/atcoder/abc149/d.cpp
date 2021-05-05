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
  long long N, K, R, S, P;
  string T;
  cin >> N >> K >> R >> S >> P;
  cin >> T;

  for (int i = K; i < N; i++) {
    if(T[i-K] == T[i]) {
      T[i] = 'X';
    }
  }

  long long ans = 0;
  for (int i = 0; i < N; i++) {
    if (T[i] == 'r') {
      ans += P;
    } else if (T[i] == 's') {
      ans += R;
    } else if (T[i] == 'p') {
      ans += S;
    }
  }

  cout << ans << endl;

  return 0;
}
