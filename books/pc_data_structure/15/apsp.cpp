#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const long long INF = (1LL<<32);
const int MAX = 300;

int n, e;
long long M[MAX][MAX];

void froyd()
{
  for (int k = 0; k < n; k++) {
    for (int j = 0; j < n; j++) {
      if (M[k][j] == INF) continue;
      for (int i = 0; i < n; i++) {
        if (M[i][k] == INF) continue;
        M[i][j] = min(M[i][j], M[i][k] + M[k][j]);
      }
    }
  }
}

void p()
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == 0) cout << " ";
      cout << M[i][j];
    }
    cout << endl;
  }
}


int main()
{
  int s, t, d;
  scanf("%d %d", &n, &e);

  for (int i = 0; i < n; i++) {
    cin >> s >> t >> d;
    M[s][t] = d;
  }

  froyd();
  p();
}
