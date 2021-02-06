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

int main(int argc, char *argv[])
{
  int N, M;
  string A[60], B[60];
  cin >> N >> M;

  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < M; i++) cin >> B[i];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < A[i].size(); j++) {

      bool ok = true;
      for (int k = 0; k < M; k++) {
        for (int l = 0; l < B[k].size() ; l++) {
          if (j + l >= A[i + k].size() || i + k >= N) {
            ok = false;
            break;
          }

          if (A[i + k][j + l] == B[k][l]) continue;
          ok = false;
          break;
        }

        if (!ok) break;
      }

      if (ok) {
        cout << "Yes" << endl;
        return 0;
      }
    }
  }

  cout << "No" << endl;
  return 0;
}
