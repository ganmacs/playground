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

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  map<int, vector<int>> M;
  for (auto& vi: V) {
    cin >> vi;
  }

  int tt = min(8, N);
  for (int i = 0; i < pow(2, tt); i++) {
    vector<int> T;
    long long vvv = 0;

    for (int j = 0; j < tt; j++) {
      if ((1 << j) & i) {
        T.push_back(j + 1);
        vvv += V[j];
      }
    }

    if (T.size() == 0) {
      continue;
    }

    int k = vvv % 200;
    if (M.find(k) != M.end()) {
      cout << "Yes" << endl;

      cout << M[k].size() << " ";
      for (auto& vi: M[k]) {
        cout << vi << " ";
      }
      puts("");

      cout << T.size() << " ";
      for (auto& vi: T) {
        cout << vi << " ";
      }
      puts("");

      return 0;
    } else {
      M[k] = T;
    }
  }

  cout << "No" << endl;
  return 0;
}
