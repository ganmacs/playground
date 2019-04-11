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
  int N, M;
  cin >> N >> M;
  pair<int, int> v[200000];

  int a, b;
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    v[i] = make_pair(b, a);
  }

  sort(v, v + M);

  int c = 0, l = 0;
  for (int i = 0; i < M; i++) {
    if (l <= v[i].second) {
      l = v[i].first;
      c++;
    }
  }

  cout << c << endl;
  return 0;
}
