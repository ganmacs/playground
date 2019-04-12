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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  int N, M, x[1000], y[1000];
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    cin >> x[i] >> y[i];
    x[i]--, y[i]--;
  }

  int ret = 1;
  for (int i = 0; i < (1<<N); i++) {
    int cc[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int j = 0; j < M; j++) {
      if ((i & 1<<x[j]) && (i & 1<<y[j])) {
        cc[x[j]]++, cc[y[j]]++;
      }
    }

    int prev = -1;
    bool ok = false;
    for (int j = 0; j < N; j++) {
      if (cc[j] != 0) {
        if (cc[j] == prev || prev == -1) {
          prev = cc[j];
          ok = true;
        } else {
          ok = false;
          break;
        }
      }
    }

    if (ok) ret = max(ret, prev + 1);
  }

  cout << min(12, ret) << endl;
  return 0;
}
