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
  for (auto& vi: V) {
    cin >> vi;
    vi--;
  }
  vector<int> A;

  for (int j = 0; j < N; j++) {
    for (int i = V.size()-1; i >= 0; i--) {
      if (V[i] == i) {
        A.push_back(V[i]);
        V.erase(V.begin() + i);
        break;
      }
    }
  }

  if (A.size() != N) {
    cout << -1 << endl;
    return 0;
  }

  reverse(A.begin(), A.end());

  for (auto& vi: A) {
    cout << (vi + 1) << endl;
  }

  return 0;
}
