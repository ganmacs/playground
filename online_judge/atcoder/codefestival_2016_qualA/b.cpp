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
  int N, a, ans = 0;;
  cin >> N;

  map<int, map<int, int> > V;

  for (int i = 0; i < N; i++) {
    cin >> a;
    a--;

    if (V[a][i]) ans++;
    V[i][a] = 1;
  }


  cout << ans << endl;
  return 0;
}
