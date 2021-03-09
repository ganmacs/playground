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

int k[15], s[15][15], p[15];
bool sw[15];

int main(int argc, char *argv[])
{
  int N, M, ans = 0;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> k[i];
    for (int j = 0; j < k[i]; j++) {
      cin >> s[i][j];
    }
  }

  for (int i = 0; i < M; i++) {
    cin >> p[i];
  }

  for (int i = 0; i < pow(2, N); i++) {
    for (int j = 0; j < N; j++) {
      sw[j] = (1 << j) & i;
    }

    int ok = true;
    for (int j = 0; j < M; j++) {
      int kkk = 0;
      for (int l = 0; l < k[j]; l++) {
        kkk += sw[s[j][l]-1];
      }

      if (kkk%2 != p[j]) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    ans++;
  }

  cout << ans << endl;
  return 0;
}
