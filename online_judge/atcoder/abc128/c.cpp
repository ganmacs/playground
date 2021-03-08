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

int k[11], s[11][11], p[11], ary[10];

int main(int argc, char *argv[])
{
  int N, M, ans = 0;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> k[i];
    ary[i] = 0;
    for (int j = 0; j < k[i]; j++) {
      cin >> s[i][j];
    }
  }

  for (int i = 0; i < M; i++) {
    cin >> p[i];
  }

  int switch_pattern[10];
  for (int i = 0; i < (1 << N); i++) {
    for (int j = 0; j < N; j++) {
      switch_pattern[j] = !!(i & (1 << j)) ? 1 : 0;
    }

    // for (int j = 0; j < N; j++) {
    //   printf("%d", switch_pattern[j]);
    // }
    // puts("");

    bool ok = true;
    for (int j = 0; j < M; j++) {
      int sum = 0;
      for (int l = 0; l < k[j]; l++) {
        sum += switch_pattern[s[j][l]-1];
      }

      if (sum % 2 != p[j]) {
        ok = false;
        break;
      }
    }

    if (ok)
      ans++;
  }

  cout << ans << endl;

  return 0;
}
