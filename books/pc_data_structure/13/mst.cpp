#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = (1 << 21);
int n;
int M[MAX][MAX], c[MAX];
int vist[MAX];

int prim()
{
  int res = 0;
  c[0] = 0;

  while (1) {
    int v = -1;
    for (int i = 0; i < n; i++) {
      if (!vist[i] && (v == -1 || c[v] > c[i])) v = i;
    }

    if (v == -1) break;
    vist[v] = true;
    res += c[v];

    for (int i = 0; i < n; i++) {
      c[i] = min(c[i], M[v][i]);
    }
  }

  return res;
}

int main()
{
  int u;
  cin >> n;

  for (int i = 0; i < n; i++) {
    vist[i] = false;
    c[i] = INF;
    for (int j = 0; j < n; j++) {
      cin >> u;
      if (u == -1) {
        M[i][j] = INF;
      } else {
        M[i][j] = u;
      }
    }
  }

  cout << prim() << endl;

  return 0;
}
