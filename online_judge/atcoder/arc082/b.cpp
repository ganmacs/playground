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
  int N, p, v = 0;
  cin >> N;
  vector<int> V;
  for (int i = 0; i < N; i++) {
    cin >> p;
    p--;
    V.push_back(p);
  }

  for (int i = 0; i < (N-1); i++) {
    if (V[i] == i) {
      v++;
      swap(V[i], V[i + 1]);
    }
  }

  if (V[N-1] == N-1) {
    v++;
  }

  cout << v << endl;
  return 0;
}
