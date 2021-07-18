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
  long long N, X;
  cin >> N >> X;

  vector<long long> L(1, 1), P(1, 1);
  for (int i = 1; i <= N; i++) {
    L.push_back(2*L[i-1] + 3);
    P.push_back(2*P[i-1] + 1);
  }

  long long ans = 0;
  for (int i = N; i >= 0; i--) {
    if (X == 0) break;

    if (i == 0) {
      ans++;
    } else if  (X == 1) {
      break;
    } else if (L[i] == X) {
      ans += P[i];
      break;
    } else if (L[i-1] + 1 == X) {
      ans += P[i-1];
      break;
    } else if (L[i-1] + 2 <= X) {
      ans += P[i-1] + 1;
      X -= (L[i-1] + 2);
    } else {
      X--;
    }
  }

  cout << ans << endl;
  return 0;
}

// B(N-1)P(N-1)B
