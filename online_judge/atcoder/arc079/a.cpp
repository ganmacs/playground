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
  int N, M, a, b;
  cin >> N >> M;
  bool ans = false;
  set<int> s;

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    if (a == 1) {
      if (s.count(b)) ans = true;
      s.insert(b);
    } else if (b == N) {
      if (s.count(a)) ans = true;
      s.insert(a);
    }
  }

  if (ans) {
    cout << "POSSIBLE" << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}
