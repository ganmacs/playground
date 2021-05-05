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

int
main()
{
  int N, a;
  string s;
  cin >> N;
  vector<pair<string, pair<int, int>>> V;

  for (int i = 0; i < N; i++) {
    cin >> s >> a;
    V.push_back(make_pair(s, make_pair(-a, i + 1)));
      }
  sort(V.begin(), V.end());

  for (auto& vi: V) {
    cout << vi.second.second << endl;
  };

  return 0;
}
