#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const long long INF = (1LL<<32);
const int MAX = 300;

int v, e;
long long M[MAX][MAX];

void floyd()
{
  int i = 0, j = 0, k = 0;
  for (k = 0; k < v; k++) {
    for (i = 0; i < v; i++) {
      if (M[i][k] == INF) continue;
      for (j = 0; j < v; j++) {
        if (M[k][j] == INF) continue;
        M[i][j] = min(M[i][j], M[i][k] + M[k][j]);
      }
    }
  }
}

void p()
{
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      if (j != 0) cout << " ";
      if (M[i][j] == INF) {
        cout << "INF";
      } else {
        cout << M[i][j];
      }
    }
    cout << endl;
  }
}

int main()
{
  int s, t, d;
  scanf("%d %d", &v, &e);

  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++)
      M[i][j] = (i == j ? 0 : INF);
  }

  for (int i = 0; i < e; i++) {
    scanf("%d %d %d", &s, &t, &d);
    M[s][t] = d;
  }


  floyd();

  bool flg = false;
  for (int i = 0; i < v; i++) {
    if (M[i][i] < 0) flg = true;
  }

  if (flg) {
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    p();
  }
}
