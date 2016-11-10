#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MAX = 102;
int M[MAX][MAX], ans[MAX], n;
bool vist[MAX];
queue<int> Q;

void bsf(int u)
{
  Q.push(u);
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();
    for (int i = 1; i <= n; i++) {
      if (M[v][i] == 1 && ans[i] == -1) {
        Q.push(i);
        ans[i] = ans[v] + 1;
      }
    }
  }
}

int main()
{
  int l, t, ii;
  cin >> n;

  for (int i = 0; i <= n; i++) {
    vist[i] = false;
    ans[i] = -1;
    for (int j = 0; j <= n; j++) {
      M[i][j] = -1;
    }
  }

  for (int i = 1; i <= n; i++) {
    cin >> l >> ii;
    for (int j = 0; j < ii; j++) {
      cin >> t;
      M[i][t] = 1;
    }
  }

  ans[1] = 0;
  bsf(1);

  for (int i = 1; i <= n; i++) {
    cout << i << " " <<  ans[i] << endl;
  }

  return 0;
}
