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
int ANS[MAXN + 1];

int main()
{
  cin >> n >> m;

  for (int i = 0; i < m; i++) cin >> C[i];

  for (int i = 0; i <= n; i++) ANS[i] = INF;
  ANS[0] = 0;

  for (int i = 0; i <= m; i++) {
    for (int j = C[i]; j <= n; j++) {
      ANS[j] = min(ANS[j], ANS[j-C[i]] + 1);
    }
  }

  cout << ANS[n] << endl;
  return 0;
}
