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
  int N, ans = 0;
  string S;
  cin >> N >> S;

  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k <= 9; k++) {
        vector<int> vv = {i, j, k};
        int l = 0;
        bool ok = false;

        for (auto& vi: vv) {
          ok = false;
          for (; l < N; l++) {
            if ((S[l]- '0') == vi) {
              ok = true;
              l++;
              break;
            }
          }
          if (!ok) break;
        };
        if (ok) ans++;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
