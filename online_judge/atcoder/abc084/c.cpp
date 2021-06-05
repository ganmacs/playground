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
  int N;
  cin >> N;
  N--;
  vector<int> C(N), S(N), F(N);
  for (int i = 0; i < N; i++) {
    cin >> C[i] >> S[i] >> F[i];
  }

  for (int i = 0; i < N; i++) {
    int ans = 0;
    for (int j = j; j < N; j++) {
      ans = max(ans, S[j]);

      int d = ans - S[j];
      if (d % F[j] == 0) {
        d = 0;
      } else {
        d = F[j]-(d % F[j]);
      }
      ans += C[j] + d;
    }
    cout << ans << endl;
  }
  printf("%d\n", 0);

  return 0;
}
