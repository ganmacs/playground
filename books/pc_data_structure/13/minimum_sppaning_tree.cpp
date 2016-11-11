#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = (1 << 21);
int M[MAX][MAX];
int A[MAX];
bool vist[MAX];
int n;

int prim()
{
  int res = 0;
  A[0] = 0;

  while (1) {
    int v = -1;
    for (int i = 0; i < n; i++) {
      if (!vist[i] && (v == -1 || A[v] > A[i])) v = i;
    }

    if (v == -1) break;
    vist[v] = true;
    res += A[v];

    for (int i = 0; i < n; i++) {
      A[i] = min(A[i], M[v][i]);
    }
  }

  return res;
}

int main()
{
  int u;
  cin >> n;
  for (int i = 0; i < n; i++) {
    A[i] = INF;
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
