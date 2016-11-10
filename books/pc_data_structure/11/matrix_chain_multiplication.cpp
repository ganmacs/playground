#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

const int M = 100;

int n;
pair<int, int> N[M + 1];
int V[M + 1][M + 1];

const int INF = (1 << 21);

int main()
{
  int r, c;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> r >> c;
    N[i] = make_pair(r, c);
  }

  for (int i = 1; i <= n; i++) V[i][i] = 0;

  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      V[i][j] = INF;

      for (int k = i; k < j; k++) {
        V[i][j] = min(V[i][j], V[i][k] + V[k+1][j] + (N[i].first * N[k].second * N[j].second));
      }
    }
  }

  cout << V[1][n] << endl;
  return 0;
}


// for (int i = 1; i <= n; i++) {
//   for (int j = i + 1; j <= n; j++) {
//     V[i][j] = INF;
//     for (int k = i; k < j; k++) {
//       V[i][j] = min(V[i][j], V[i][k] + V[k+1][j] + (N[i].first * N[k].second * N[j].second));
//     }
//   }
// }
