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

// const int INF = 10000000;

int A[100];
int x[100][100][2];

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];

    for (int j = 0; j < A[i]; j++) {
      cin >> x[i][j][0] >> x[i][j][1];
      // printf("%d %d %d\n", i, x[i][j][0], x[i][j][1]);
    }
  }

  int all[16], ans = 0;
  for (int i = 0; i < (1 << N); i++) {

    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        all[j] = 1;
      } else {
        all[j] = 0;
      }
    }

    // for (int j = 0; j < N; j++) {
    //   printf("%d", all[j]);
    // }
    // puts("");

    bool f = true;
    int tans = 0;
    for (int j = 0; j < N; j++) {
      if (all[j] == 0) continue; // check unhonesty?
      tans++;

      for (int l = 0; l < A[j]; l++) {
        if (all[x[j][l][0]-1] != x[j][l][1]) {
          f = false;
          break;
        }
      }
    }
    if (!f) {
      tans = 0;
    }

    ans = max(tans, ans);
  }

  cout << ans << endl;
  return 0;
}
