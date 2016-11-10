#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

const int M = 100;
const int INF = (1 << 21);

int main()
{
  int n, N[M + 1][M + 1], c, r;
  pair<int, int> v[M + 1];
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> r >> c;
    v[i] = make_pair(r, c);
  }

  for (int i = 1; i < n; i++) N[i][i] = 0;

  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      N[i][j] = INF;

      for (int k = i; k < j; k++) {
        N[i][j] = min(N[i][j], N[i][k] + N[k+1][j] + v[i].first * v[k].second * v[j].second);
      }
    }
  }

  cout << N[1][n] << endl;
  return 0;
}

// for (int i = 1; i <= n; i++) {
//   for (int k = 1; k <= n; k++) {
//     cout << N[i][k] << " ";
//   }
//   cout << endl;
// }
