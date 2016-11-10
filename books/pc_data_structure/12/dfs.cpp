#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

const int MAX = 102;
int n;
int M[MAX][MAX];
bool vist[MAX];
stack<int> S;
int ANS[MAX][2];

int next(int u)
{
  // need cache?
  for (int i = 1; i <= n; i++) {
    if (M[u][i] && !vist[i]) {
      return i;
    }
  }

  return -1;
}

int t = 0;

void dfs_visit(int u)
{
  S.push(u);
  ANS[u][0] = ++t;
  vist[u] = true;

  while (!S.empty()) {
    int u = S.top();
    int ii = next(u);

    if (ii != -1) {
      S.push(ii);
      ANS[ii][0] = ++t;
      vist[ii] = true;
    } else {
      S.pop();
      ANS[u][1] = ++t;
    }
  }
}


int main()
{
  int l, t, ii;
  cin >> n;

  for (int i = 0; i <= n; i++) {
    vist[i] = false;
    for (int j = 0; j <= n; j++) {
      M[i][j] = 0;
    }
  }

  for (int i = 1; i <= n; i++) {
    cin >> l >> ii;
    for (int j = 0; j < ii; j++) {
      cin >> t;
      M[i][t] = 1;
    }
  }

  for (int i = 1; i < n; i++) {
    if (!vist[i]) dfs_visit(i);
  }

  for (int i = 1; i <= n; i++) {
    cout << i << " " << ANS[i][0] << " " << ANS[i][1] << endl;
  }

  return 0;
}
