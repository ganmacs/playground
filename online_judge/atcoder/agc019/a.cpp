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
  unsigned long long int Q, H, S, D, N;
  unsigned long long int ans = 1e19;
  cin >> Q >> H >> S >> D;
  cin >> N;

  Q *= 4;
  H *= 2;
  unsigned long long  int KKK = min(Q, min(H, S));

  for (unsigned long long int i = 0; i <= N; i++) {
    if ((N-i) % 2 == 0) {
      ans = min(KKK*i + D*((N-i)/2), ans);
    }
  }

  cout << ans << endl;

  return 0;
}
