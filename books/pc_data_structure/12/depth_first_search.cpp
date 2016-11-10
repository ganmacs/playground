#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 102;
int n;
int I[MAX];
int M[MAX][MAX];
int ANS[MAX][2];
bool vist[MAX];

int dfs(int ni, int t)
{
  int dt = 1;
  vist[ni] = true;
  ANS[ni][0] = t + dt;

  for (int i = 1; i <= n; i++) {
    if (M[ni][i] == 1 && !vist[i]){
      dt += dfs(i, t + dt);
    }
  }

  dt++;
  ANS[ni][1] = t + dt;
  return dt;
}

int main()
{
  int l, t;
  cin >> n;

  for (int i = 0; i <= n; i++) {
    vist[i] = false;
    for (int j = 0; j <= n; j++) {
      M[i][j] = 0;
    }
  }

  for (int i = 1; i <= n; i++) {
    cin >> l >> I[i];
    for (int j = 0; j < I[i]; j++) {
      cin >> t;
      M[i][t] = 1;
    }
  }

  int tt = 0;
  for (int i = 1; i <= n; i++) {
    if (!vist[i]) {
      tt += dfs(i, tt);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << i << " " << ANS[i][0] << " " << ANS[i][1] << endl;
  }

  return 0;
}
