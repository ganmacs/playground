#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

bool ma[1000][1000] = {};
int ans = 0;
int N, M, a[1000], b[1000];

void perm(int *a, int n) {
  if (n == 1) {
    if (ma[a[0]][a[1]]) {
      ans++;
    }
    return;
  }

  for (int i = 0; i < n; i++) {
    swap(a[i], a[n-1]);

    if (n < N) {
      if (ma[a[n-1]][a[n]]) perm(a, n-1);
    } else {
      if (a[n-1] == 1) perm(a, n-1);
    }

    swap(a[n-1], a[i]);
  }
}

int main(int argc, char *argv[])
{
  vector<int> q[1000];

  cin >> N >> M;

  int c, d;
  for (int i = 0; i < M; i++) {
    cin >> c >> d;
    ma[c][d] = true;
    ma[d][c] = true;
  }

  for (int i = 1; i <= N; i++) a[i-1] = i;
  perm(a, N);

  cout << ans << endl;
}
