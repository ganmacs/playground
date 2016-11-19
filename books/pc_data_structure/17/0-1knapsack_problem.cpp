#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 150;
const int MAXW = 10050;

int n, w;
pair<int, int> in[MAXN];
int ANS[MAXN + 1][MAXW + 1];

int main()
{
  int v, ww;
  cin >> n >> w;

  for (int i = 1; i <= n; i++) {
    cin >> v >> ww;
    // value, weight
    in[i] = make_pair(v, ww);
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= w; j++)
      ANS[i][j] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= w; j++) {
      if (j - in[i].second >= 0) {
        ANS[i][j] = max(ANS[i-1][j], in[i].first + ANS[i-1][j - in[i].second]);
      } else {
        ANS[i][j] = ANS[i-1][j];
      }
    }
  }
  cout << ANS[n][w] << endl;
  return 0;
}
