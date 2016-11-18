#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 50000;
const int MAXM = 20;
const int INF = (1 << 30);

int n, m;
int C[MAXM + 1];
int A[MAXM + 1][MAXN + 1];

int main()
{
  cin >> n >> m;

  for (int i = 1; i <= m; i++) cin >> C[i];

  for (int i = 0; i <= n; i++) A[0][i] = INF;
  for (int i = 0; i <= m; i++) A[i][0] = 0;

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (j - C[i] >= 0) {
        A[i][j] = min(A[i-1][j], A[i][j-C[i]] + 1);
      } else {
        A[i][j] = A[i-1][j];
      }
    }
  }

  cout << A[m][n] << endl;
  return 0;
}
