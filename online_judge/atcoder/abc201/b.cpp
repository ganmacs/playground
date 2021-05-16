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
  int N, a;
  cin >> N;
  string s;
  vector<pair<int, string>> V(N);

  for (auto& vi: V) {
    cin >> s >> a;
    V.push_back(make_pair(-a, s));
  }

  sort(V.begin(), V.end());

  cout << V[1].second << endl;
  return 0;
}
