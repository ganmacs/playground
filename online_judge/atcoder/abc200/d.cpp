#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{

  int N;
  cin >> N;
  vector<long long> V(N);
  map<int, vector<int>> M;
  for (auto& vi: V) {
    cin >> vi;
  };

  int m = min(N, 8);
  for (int i = 0; i < (1 << m); i++) {
    vector<int> s;
    int c = 0;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        s.push_back(j + 1);
        c += V[j];
        c %= 200;
      }
    }

    if (M[c].size() != 0) {
      cout << "Yes\n";
      cout << M[c].size() << " ";
      for (auto& vi: M[c]) {
        cout << vi << " ";
      };
      puts("");

      cout << s.size() << " ";
      for (auto& vi: s) {
        cout << vi << " ";
      };
      puts("");

      return 0;
    } else {
      M[c] = s;
    }
  }

  cout << "No\n";

  return 0;
}
