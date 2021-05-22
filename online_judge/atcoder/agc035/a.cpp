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

int N;
vector<int> V;
map<int, int> M;

bool solve() {
  if (N % 3 != 0)  {
    return (M[0] == N);
  }

  for (auto& vi: M) {
    V.push_back(vi.first);
  };

  if (M.size() == 3) {
    if ((V[0] ^ V[1] ^ V[2]) != 0) return false;
    return (M[V[0]] == M[V[1]] && M[V[1]] == M[V[2]]);
  } else if (M.size() == 2) {
    return (M[0] == N/3);
  } else {
    return (M[0] == N);
  }
}

int main()
{
  cin >> N;

  int a;
  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }

  if (solve()) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}
