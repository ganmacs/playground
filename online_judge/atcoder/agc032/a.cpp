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
#include <algorithm>

using namespace std;

int main()
{

  int N;
  cin >> N;
  vector<int> V(N), A;
  for (auto& vi: V) {
    cin >> vi;
  };

  for (int j = 0; j < N; j++) {
    bool f = false;
    for (int i = V.size()-1; i >= 0; i--) {
      if (V[i] == i + 1) {
        A.push_back(V[i]);
        V.erase(V.begin() + i);
        f = true;
        break;
      }
    }

    if (!f) {
      cout << -1 << endl;
      return 0;
    }
  }

  reverse(A.begin(), A.end());
  for (auto& vi: A) {
    cout << vi << endl;
  };

  return 0;
}
